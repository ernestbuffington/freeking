#pragma once

#include "Vector.h"
#include "Matrix4x4.h"
#include <map>
#include <memory>
#include <stack>
#include <string>
#include <vector>

namespace Freeking
{
	class Texture2D;
	class VertexBinding;
	class VertexBuffer;
	class Shader;
	class Material;
	class Font;
	class TextureSampler;

	class SpriteBatch
	{
	public:

		static std::shared_ptr<SpriteBatch> Debug;
		static Matrix4x4 ProjectionMatrix;
		static Matrix4x4 ViewMatrix;
		static float ViewportWidth;
		static float ViewportHeight;

		SpriteBatch(size_t = 1000);

		void Flush(const Matrix4x4&, float = 1.0f);
		void DrawText(const Font*, const std::string&, const Vector2f&, const Vector4f&, float);
		void Draw(Texture2D*, const Vector2f&, float, const Vector4f&);
		void Draw(Texture2D*, const Vector2f&, const Vector2f&, const Vector4f&);
		void Draw(Texture2D*, const Vector2f&, const Vector2f&, float, const Vector4f&);
		void Draw(Texture2D*, const Vector2f&, const Vector2f&, const Vector2f&, const Vector2f&, const Vector4f&, bool = false);
		void Draw9Slice(Texture2D*, const Vector2f&, const Vector2f&, const Vector4f&, const Vector4f&, bool = true);
		void Draw9Slice(Texture2D*, const Vector2f&, const Vector2f&, const Vector2f&, const Vector2f&, const Vector4f&, const Vector4f&, bool = true);

		void EnableClipping(bool clipping) { _clipping = clipping; }
		void SetClippingRect(const Vector4f& clippingRect) { _clippingRect = clippingRect; }

		size_t GetDrawCallCount() const { return _drawCallCount; }

	private:

		static std::shared_ptr<Material> GetSpriteMaterial();
		static std::shared_ptr<Material> GetTextMaterial();

		struct Sprite
		{
			Sprite(Texture2D*, const Vector2f&, const Vector2f&, float, const Vector4f&);
			Sprite(Texture2D*, const Vector2f&, const Vector2f&, const Vector2f&, const Vector2f&, const Vector4f&);

			Texture2D* _texture;
			Vector2f _position;
			Vector2f _size;
			Vector2f _uv1;
			Vector2f _uv2;
			Vector4f _colour;
			float _angle;
		};

		struct Slice
		{
			Vector2f _uv1;
			Vector2f _uv2;
			Vector2f _drawPosition;
			Vector2f _drawSize;
		};

		struct NineSliceProperties
		{
			NineSliceProperties(
				const Vector2f&,
				const Vector2f&,
				const Vector2f&,
				const Vector2f&,
				const Vector2f&);

			void GetTopLeftSlice(Slice&) const;
			void GetTopRightSlice(Slice&) const;
			void GetBottomLeftSlice(Slice&) const;
			void GetBottomRightSlice(Slice&) const;
			void GetTopMidSlice(Slice&) const;
			void GetBottomMidSlice(Slice&) const;
			void GetLeftMidSlice(Slice&) const;
			void GetRightMidSlice(Slice&) const;
			void GetMidSlice(Slice&) const;

			const Vector2f _glyphSize;
			const Vector2f _topLeftSlicePx;
			const Vector2f _bottomRightSlicePx;
			const Vector2f _topLeftSlice;
			const Vector2f _bottomRightSlice;
			const Vector2f _drawPosition;
			const Vector2f _drawSize;
		};

		void DrawSprites(const Matrix4x4&, float, const std::shared_ptr<Material>&, std::vector<SpriteBatch::Sprite>&);
		void DrawSlice(Texture2D*, const Slice&, const Vector4f&);
		static void TransformUV(Vector2f&, const Vector2f&, const Vector2f&, const Vector2f&);
		static void TransformUVs(Slice&, const Vector2f&, const Vector2f&, const Vector2f&);
		bool IsSpriteInsideClippingRect(const Vector2f&, const Vector2f&);

		std::vector<Sprite> _spritesToDraw;
		std::vector<Sprite> _textToDraw;
		bool _clipping;
		Vector4f _clippingRect;
		size_t _drawCallCount;
		size_t _maxSpriteCount;
		std::vector<float> _vertexData;
		std::unique_ptr<VertexBuffer> _vertexBuffer;
		std::unique_ptr<VertexBinding> _vertexBinding;
	};
}
