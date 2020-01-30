#include "SpriteBatch.h"
#include "Shader.h"
#include "Material.h"
#include "VertexBinding.h"
#include "VertexBuffer.h"
#include "Texture2D.h"
#include "Font.h"
#include "Maths.h"
#include "Util.h"
#include "TextureSampler.h"

namespace Freeking
{
	std::shared_ptr<Material> SpriteBatch::GetSpriteMaterial()
	{
		static auto material = std::make_shared<Material>(Shader::Library.Get("Shaders/Sprite.shader"));
		return material;
	}

	std::shared_ptr<Material> SpriteBatch::GetTextMaterial()
	{
		static auto material = std::make_shared<Material>(Shader::Library.Get("Shaders/Text.shader"));
		return material;
	}

	SpriteBatch::Sprite::Sprite(
		Texture2D* texture,
		const Vector2f& position,
		const Vector2f& size,
		float angle,
		const Vector4f& colour) :
		_texture(texture),
		_position(position),
		_size(size),
		_uv1(0, 1),
		_uv2(1, 0),
		_colour(colour),
		_angle(angle)
	{
	}

	SpriteBatch::Sprite::Sprite(
		Texture2D* texture,
		const Vector2f& position,
		const Vector2f& size,
		const Vector2f& uv1,
		const Vector2f& uv2,
		const Vector4f& colour) :
		_texture(texture),
		_position(position),
		_size(size),
		_uv1(uv1),
		_uv2(uv2),
		_colour(colour),
		_angle(0.0f)
	{
	}

	SpriteBatch::SpriteBatch(size_t maxSpriteCount) :
		_clipping(false),
		_drawCallCount(0),
		_maxSpriteCount(maxSpriteCount)
	{
		static const size_t vertSize = 8;
		static const size_t faceVertCount = 6;
		static const size_t vertStride = vertSize * sizeof(float);

		_vertexBuffer = std::make_unique<VertexBuffer>(nullptr, _maxSpriteCount * faceVertCount, vertStride, GL_DYNAMIC_DRAW);

		ArrayElement vertexLayout[] =
		{
			ArrayElement(_vertexBuffer.get(), 0, 2, ElementType::Float, vertStride, 0),
			ArrayElement(_vertexBuffer.get(), 1, 2, ElementType::Float, vertStride, 2 * sizeof(float)),
			ArrayElement(_vertexBuffer.get(), 2, 4, ElementType::Float, vertStride, 4 * sizeof(float)),
		};

		_vertexBinding = std::make_unique<VertexBinding>();
		_vertexBinding->Create(vertexLayout, 3, *_vertexBuffer);

		_vertexData.resize(_maxSpriteCount * faceVertCount * vertSize);
	}

	void SpriteBatch::DrawText(const Font* font, const std::string& text, const Vector2f& position, const Vector4f& colour, float scale)
	{
		if (font == nullptr)
		{
			return;
		}

		Font::Character character;
		Vector2f curPosition = position;
		float lineHeight = font->GetLineHeight() * scale;
		curPosition.y += lineHeight;

		for (const char& c : text)
		{
			if (c == '\n')
			{
				curPosition.x = position.x;
				curPosition.y += lineHeight;

				continue;
			}

			if (!font->TryGetCharacter(c, character))
			{
				continue;
			}

			Texture2D* pageTexture = font->GetPageTexture(character.page);
			float pageWidth = (float)pageTexture->GetWidth();
			float pageHeight = (float)pageTexture->GetHeight();

			Draw(pageTexture,
				curPosition + Vector2f(character.xoffset * scale, character.yoffset * scale),
				Vector2f(character.x / pageWidth, character.y / pageHeight),
				Vector2f((character.x + character.width) / pageWidth, (character.y + character.height) / pageHeight),
				Vector2f(character.width * scale, character.height * scale),
				colour,
				true);

			curPosition += Vector2f((character.xadvance) * scale, 0);
		}
	}

	void SpriteBatch::Draw(
		Texture2D* texture,
		const Vector2f& position,
		float angle,
		const Vector4f& colour)
	{
		_spritesToDraw.push_back(Sprite(texture, position, Vector2f((float)texture->GetWidth(), (float)texture->GetHeight()), angle, colour));
	}

	void SpriteBatch::Draw(
		Texture2D* texture,
		const Vector2f& position,
		const Vector2f& size,
		const Vector4f& colour)
	{
		float u1 = 0.0f;
		float v1 = 0.0f;
		float u2 = 1.0f;
		float v2 = 1.0f;
		Vector2f newPosition = position;
		Vector2f newSize = size;

		if (_clipping)
		{
			if (!IsSpriteInsideClippingRect(position, size))
			{
				return;
			}

			float newleft = Math::Clamp(position.x, (float)_clippingRect.x, (float)_clippingRect.z);
			float newtop = Math::Clamp(position.y, (float)_clippingRect.y, (float)_clippingRect.w);
			float newright = Math::Clamp(position.x + size.x, (float)_clippingRect.x, (float)_clippingRect.z);
			float newbottom = Math::Clamp(position.y + size.y, (float)_clippingRect.y, (float)_clippingRect.w);

			newPosition = Vector2f(newleft, newtop);
			newSize = Vector2f(newright - newleft, newbottom - newtop);

			float difleft = newleft - position.x;
			float diftop = newtop - position.y;
			float difright = newright - (position.x + size.x);
			float difbottom = newbottom - (position.y + size.y);

			difleft /= size.x;
			diftop /= size.y;
			difright /= size.x;
			difbottom /= size.y;

			float uwidth = u2 - u1;
			float vheight = v2 - v1;

			u1 = u1 + (uwidth * difleft);
			u2 = u2 + (uwidth * difright);
			v1 = v1 + (vheight * diftop);
			v2 = v2 + (vheight * difbottom);
		}

		_spritesToDraw.push_back(Sprite(texture, newPosition, newSize, Vector2f(u1, v1), Vector2f(u2, v2), colour));
	}

	void SpriteBatch::Draw(
		Texture2D* texture,
		const Vector2f& position,
		const Vector2f& size,
		float angle,
		const Vector4f& colour)
	{
		_spritesToDraw.push_back(Sprite(texture, position, size, angle, colour));
	}

	void SpriteBatch::Draw(
		Texture2D* texture,
		const Vector2f& position,
		const Vector2f& uv1,
		const Vector2f& uv2,
		const Vector2f& size,
		const Vector4f& colour,
		bool isText)
	{
		float u1 = uv1.x;
		float v1 = uv1.y;
		float u2 = uv2.x;
		float v2 = uv2.y;
		Vector2f newPosition = position;
		Vector2f newSize = size;

		if (_clipping)
		{
			if (!IsSpriteInsideClippingRect(position, size))
			{
				return;
			}

			float newleft = Math::Clamp(position.x, (float)_clippingRect.x, (float)_clippingRect.z);
			float newtop = Math::Clamp(position.y, (float)_clippingRect.y, (float)_clippingRect.w);
			float newright = Math::Clamp(position.x + size.x, (float)_clippingRect.x, (float)_clippingRect.z);
			float newbottom = Math::Clamp(position.y + size.y, (float)_clippingRect.y, (float)_clippingRect.w);

			newPosition = Vector2f(newleft, newtop);
			newSize = Vector2f(newright - newleft, newbottom - newtop);

			float difleft = newleft - position.x;
			float diftop = newtop - position.y;
			float difright = newright - (position.x + size.x);
			float difbottom = newbottom - (position.y + size.y);

			difleft /= size.x;
			diftop /= size.y;
			difright /= size.x;
			difbottom /= size.y;

			float uwidth = u2 - u1;
			float vheight = v2 - v1;

			u1 = u1 + (uwidth * difleft);
			u2 = u2 + (uwidth * difright);
			v1 = v1 + (vheight * diftop);
			v2 = v2 + (vheight * difbottom);
		}

		if (isText)
		{
			_textToDraw.push_back(Sprite(texture, newPosition, newSize, Vector2f(u1, v1), Vector2f(u2, v2), colour));
		}
		else
		{
			_spritesToDraw.push_back(Sprite(texture, newPosition, newSize, Vector2f(u1, v1), Vector2f(u2, v2), colour));
		}
	}

	SpriteBatch::NineSliceProperties::NineSliceProperties(
		const Vector2f& topLeftSlicePx,
		const Vector2f& bottomRightSlicePx,
		const Vector2f& glyphSize,
		const Vector2f& drawPosition,
		const Vector2f& drawSize) :
		_topLeftSlicePx(topLeftSlicePx),
		_bottomRightSlicePx(bottomRightSlicePx),
		_topLeftSlice(topLeftSlicePx / glyphSize),
		_bottomRightSlice(bottomRightSlicePx / glyphSize),
		_glyphSize(glyphSize),
		_drawPosition(drawPosition),
		_drawSize(drawSize)
	{
	}

	void SpriteBatch::DrawSlice(Texture2D* texture, const SpriteBatch::Slice& slice, const Vector4f& colour)
	{
		Draw(texture, slice._drawPosition, slice._uv1, slice._uv2, slice._drawSize, colour);
	}

	void SpriteBatch::NineSliceProperties::GetTopLeftSlice(Slice& slice) const
	{
		slice._uv1.x = 0.0f;
		slice._uv1.y = 1.0f;
		slice._uv2.x = _topLeftSlice.x;
		slice._uv2.y = 1.0f - _topLeftSlice.y;
		slice._drawPosition = _drawPosition;
		slice._drawSize = _topLeftSlicePx;
	}

	void SpriteBatch::NineSliceProperties::GetTopRightSlice(Slice& slice) const
	{
		slice._uv1.x = 1.0f - _bottomRightSlice.x;
		slice._uv1.y = 1.0f;
		slice._uv2.x = 1.0f;
		slice._uv2.y = 1.0f - _topLeftSlice.y;
		slice._drawPosition.x = _drawPosition.x + _drawSize.x - _bottomRightSlicePx.x;
		slice._drawPosition.y = _drawPosition.y;
		slice._drawSize.x = _bottomRightSlicePx.x;
		slice._drawSize.y = _topLeftSlicePx.y;
	}

	void SpriteBatch::NineSliceProperties::GetBottomLeftSlice(Slice& slice) const
	{
		slice._uv1.x = 0.0f;
		slice._uv1.y = _bottomRightSlice.y;
		slice._uv2.x = _topLeftSlice.x;
		slice._uv2.y = 0.0f;
		slice._drawPosition.x = _drawPosition.x;
		slice._drawPosition.y = _drawPosition.y + _drawSize.y - _bottomRightSlicePx.y;
		slice._drawSize.x = _topLeftSlicePx.x;
		slice._drawSize.y = _bottomRightSlicePx.y;
	}

	void SpriteBatch::NineSliceProperties::GetBottomRightSlice(Slice& slice) const
	{
		slice._uv1.x = 1.0f - _bottomRightSlice.x;
		slice._uv1.y = _bottomRightSlice.y;
		slice._uv2.x = 1.0f;
		slice._uv2.y = 0.0f;
		slice._drawPosition = _drawPosition + _drawSize - _bottomRightSlicePx;
		slice._drawSize = _bottomRightSlicePx;
	}

	void SpriteBatch::NineSliceProperties::GetTopMidSlice(Slice& slice) const
	{
		slice._uv1.x = _topLeftSlice.x;
		slice._uv1.y = 1.0f;
		slice._uv2.x = 1.0f - _bottomRightSlice.x;
		slice._uv2.y = 1.0f - _topLeftSlice.y;
		slice._drawPosition.x = _drawPosition.x + _topLeftSlicePx.x;
		slice._drawPosition.y = _drawPosition.y;
		slice._drawSize.x = _drawSize.x - _topLeftSlicePx.x - _bottomRightSlicePx.x;
		slice._drawSize.y = _topLeftSlicePx.y;
	}

	void SpriteBatch::NineSliceProperties::GetBottomMidSlice(Slice& slice) const
	{
		slice._uv1.x = _topLeftSlice.x;
		slice._uv1.y = _bottomRightSlice.y;
		slice._uv2.x = 1.0f - _bottomRightSlice.x;
		slice._uv2.y = 0.0f;
		slice._drawPosition.x = _drawPosition.x + _topLeftSlicePx.x;
		slice._drawPosition.y = _drawPosition.y + _drawSize.y - _bottomRightSlicePx.y;
		slice._drawSize.x = _drawSize.x - _topLeftSlicePx.x - _bottomRightSlicePx.x;
		slice._drawSize.y = _bottomRightSlicePx.y;
	}

	void SpriteBatch::NineSliceProperties::GetLeftMidSlice(Slice& slice) const
	{
		slice._uv1.x = 0.0f;
		slice._uv1.y = 1.0f - _topLeftSlice.y;
		slice._uv2.x = _topLeftSlice.x;
		slice._uv2.y = _bottomRightSlice.y;
		slice._drawPosition.x = _drawPosition.x;
		slice._drawPosition.y = _drawPosition.y + _topLeftSlicePx.y;
		slice._drawSize.x = _topLeftSlicePx.x;
		slice._drawSize.y = _drawSize.y - _bottomRightSlicePx.y - _topLeftSlicePx.y;
	}

	void SpriteBatch::NineSliceProperties::GetRightMidSlice(Slice& slice) const
	{
		slice._uv1.x = 1.0f - _bottomRightSlice.x;
		slice._uv1.y = 1.0f - _topLeftSlice.y;
		slice._uv2.x = 1.0f;
		slice._uv2.y = _bottomRightSlice.y;
		slice._drawPosition.x = _drawPosition.x + _drawSize.x - _bottomRightSlicePx.x;
		slice._drawPosition.y = _drawPosition.y + _topLeftSlicePx.y;
		slice._drawSize.x = _bottomRightSlicePx.x;
		slice._drawSize.y = _drawSize.y - _bottomRightSlicePx.y - _topLeftSlicePx.y;
	}

	void SpriteBatch::NineSliceProperties::GetMidSlice(Slice& slice) const
	{
		slice._uv1.x = _topLeftSlice.x;
		slice._uv1.y = 1.0f - _topLeftSlice.y;
		slice._uv2.x = 1.0f - _bottomRightSlice.x;
		slice._uv2.y = _bottomRightSlice.y;
		slice._drawPosition = _drawPosition + _topLeftSlicePx;
		slice._drawSize = _drawSize - _topLeftSlicePx - _bottomRightSlicePx;
	}

	void SpriteBatch::Draw9Slice(
		Texture2D* texture,
		const Vector2f& position,
		const Vector2f& size,
		const Vector4f& margin,
		const Vector4f& colour,
		bool drawCenter)
	{
		Slice slice;
		const NineSliceProperties properties(Vector2f(margin.x, margin.y), Vector2f(margin.z, margin.w), Vector2f((float)texture->GetWidth(), (float)texture->GetHeight()), position, size);

		properties.GetTopLeftSlice(slice);
		DrawSlice(texture, slice, colour);

		properties.GetTopRightSlice(slice);
		DrawSlice(texture, slice, colour);

		properties.GetBottomLeftSlice(slice);
		DrawSlice(texture, slice, colour);

		properties.GetBottomRightSlice(slice);
		DrawSlice(texture, slice, colour);

		properties.GetTopMidSlice(slice);
		DrawSlice(texture, slice, colour);

		properties.GetBottomMidSlice(slice);
		DrawSlice(texture, slice, colour);

		properties.GetLeftMidSlice(slice);
		DrawSlice(texture, slice, colour);

		properties.GetRightMidSlice(slice);
		DrawSlice(texture, slice, colour);

		if (drawCenter)
		{
			properties.GetMidSlice(slice);
			DrawSlice(texture, slice, colour);
		}
	}

	void SpriteBatch::TransformUV(Vector2f& uv, const Vector2f& glyphSize, const Vector2f& offset, const Vector2f& sheetSize)
	{
		uv = Vector2f(offset.x, sheetSize.y - offset.y - glyphSize.y) / sheetSize + uv * glyphSize / sheetSize;
	}

	void SpriteBatch::TransformUVs(Slice& slice, const Vector2f& glyphSize, const Vector2f& offset, const Vector2f& sheetSize)
	{
		TransformUV(slice._uv1, glyphSize, offset, sheetSize);
		TransformUV(slice._uv2, glyphSize, offset, sheetSize);
	}

	void SpriteBatch::Draw9Slice(
		Texture2D* texture,
		const Vector2f& position,
		const Vector2f& size,
		const Vector2f& glyphPosition,
		const Vector2f& glyphSize,
		const Vector4f& margin,
		const Vector4f& colour,
		bool drawCenter)
	{
		Slice slice;
		Vector2f sheetSize((float)texture->GetWidth(), (float)texture->GetHeight());
		const NineSliceProperties properties(Vector2f(margin.x, margin.y), Vector2f(margin.z, margin.w), glyphSize, position, size);

		properties.GetTopLeftSlice(slice);
		TransformUVs(slice, glyphSize, glyphPosition, sheetSize);
		DrawSlice(texture, slice, colour);

		properties.GetTopRightSlice(slice);
		TransformUVs(slice, glyphSize, glyphPosition, sheetSize);
		DrawSlice(texture, slice, colour);

		properties.GetBottomLeftSlice(slice);
		TransformUVs(slice, glyphSize, glyphPosition, sheetSize);
		DrawSlice(texture, slice, colour);

		properties.GetBottomRightSlice(slice);
		TransformUVs(slice, glyphSize, glyphPosition, sheetSize);
		DrawSlice(texture, slice, colour);

		properties.GetTopMidSlice(slice);
		TransformUVs(slice, glyphSize, glyphPosition, sheetSize);
		DrawSlice(texture, slice, colour);

		properties.GetBottomMidSlice(slice);
		TransformUVs(slice, glyphSize, glyphPosition, sheetSize);
		DrawSlice(texture, slice, colour);

		properties.GetLeftMidSlice(slice);
		TransformUVs(slice, glyphSize, glyphPosition, sheetSize);
		DrawSlice(texture, slice, colour);

		properties.GetRightMidSlice(slice);
		TransformUVs(slice, glyphSize, glyphPosition, sheetSize);
		DrawSlice(texture, slice, colour);

		if (drawCenter)
		{
			properties.GetMidSlice(slice);
			TransformUVs(slice, glyphSize, glyphPosition, sheetSize);
			DrawSlice(texture, slice, colour);
		}
	}

	void SpriteBatch::Flush(const Matrix4x4& proj, float scale)
	{
		if (_spritesToDraw.empty() && _textToDraw.empty())
		{
			return;
		}

		_drawCallCount = 0;

		glDisable(GL_DEPTH_TEST);

		_vertexBinding->Bind();
		TextureSampler::GetDefault()->Bind(0);

		const auto& spriteMaterial = GetSpriteMaterial();
		if (spriteMaterial)
		{
			DrawSprites(proj, scale, spriteMaterial, _spritesToDraw);
		}

		const auto& textMaterial = GetTextMaterial();
		if (textMaterial)
		{
			DrawSprites(proj, scale, textMaterial, _textToDraw);
		}

		glBindSampler(0, 0);
		_vertexBinding->Unbind();

		glEnable(GL_DEPTH_TEST);

	}

	void SpriteBatch::DrawSprites(const Matrix4x4& proj, float scale, const std::shared_ptr<Material>& material, std::vector<SpriteBatch::Sprite>& sprites)
	{
		material->SetParameterValue("projMatrix", proj);
		material->Apply();

		static const size_t vertSize = 8;
		static const size_t faceVertCount = 6;
		static const size_t vertStride = vertSize * sizeof(float);
		static const uint32_t faceIndices[] = { 0, 1, 2, 2, 3, 0 };

		size_t basePos = 0;
		size_t maxSpriteBatch = sprites.size();
		if (maxSpriteBatch > _maxSpriteCount)
		{
			maxSpriteBatch = _maxSpriteCount;
		}

		while (basePos < sprites.size() && maxSpriteBatch > 0)
		{
			size_t searchPos = basePos;
			auto batchTexture = sprites[basePos]._texture;

			while (searchPos < sprites.size() && (searchPos - basePos) < maxSpriteBatch && sprites[searchPos]._texture == batchTexture)
			{
				searchPos++;
			}

			if (batchTexture != nullptr)
			{
				batchTexture->Bind(0);
			}

			for (size_t i = basePos; i < searchPos; ++i)
			{
				float* buffer = &_vertexData[(i - basePos) * faceVertCount * vertSize];
				const Sprite& sprite = sprites[i];

				for (size_t j = 0; j < faceVertCount; ++j)
				{
					buffer[4 + vertSize * j] = sprite._colour.x;
					buffer[5 + vertSize * j] = sprite._colour.y;
					buffer[6 + vertSize * j] = sprite._colour.z;
					buffer[7 + vertSize * j] = sprite._colour.w;
				}

				Vector2f vertexPositions[4] = {
					Vector2f(-(sprite._size.x / 2), -(sprite._size.y / 2)),
					Vector2f(-(sprite._size.x / 2), sprite._size.y / 2),
					Vector2f(sprite._size.x / 2, sprite._size.y / 2),
					Vector2f(sprite._size.x / 2, -(sprite._size.y / 2)),
				};

				Vector2f vertexTextureCoords[4] = {
					Vector2f(sprite._uv1.x, sprite._uv1.y),
					Vector2f(sprite._uv1.x, sprite._uv2.y),
					Vector2f(sprite._uv2.x, sprite._uv2.y),
					Vector2f(sprite._uv2.x, sprite._uv1.y),
				};

				for (size_t j = 0; j < 4; ++j)
				{
					float cosAngle = cos(Math::DegreesToRadians(sprite._angle));
					float sinAngle = sin(Math::DegreesToRadians(sprite._angle));

					Vector2f p = vertexPositions[j];
					vertexPositions[j].x = p.x * cosAngle - p.y * sinAngle;
					vertexPositions[j].y = p.y * cosAngle + p.x * sinAngle;
					vertexPositions[j] += sprite._position + (sprite._size * 0.5f);
				}

				for (size_t j = 0; j < faceVertCount; ++j)
				{
					size_t bufferIndex = j * vertSize;
					size_t vertexIndex = faceIndices[j];

					buffer[bufferIndex] = vertexPositions[vertexIndex].x * scale;
					buffer[bufferIndex + 1] = vertexPositions[vertexIndex].y * scale;
					buffer[bufferIndex + 2] = vertexTextureCoords[vertexIndex].x;
					buffer[bufferIndex + 3] = vertexTextureCoords[vertexIndex].y;
				}
			}

			_vertexBuffer->UpdateBuffer(_vertexData.data(), 0, (searchPos - basePos) * faceVertCount * vertStride);

			glDrawArrays(GL_TRIANGLES, 0, (GLsizei)((searchPos - basePos) * faceVertCount));

			_drawCallCount++;

			basePos = searchPos;
		}

		material->Unbind();	

		sprites.clear();
	}

	bool SpriteBatch::IsSpriteInsideClippingRect(const Vector2f& position, const Vector2f& size)
	{
		return !((position.x >= _clippingRect.z) ||
			(position.x + size.x <= _clippingRect.x) ||
			(position.y >= _clippingRect.w) ||
			(position.y + size.y <= _clippingRect.y));
	}
}
