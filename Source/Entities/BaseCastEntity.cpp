#include "BaseCastEntity.h"
#include "DynamicModel.h"
#include "Shader.h"
#include "Renderer.h"
#include "LineRenderer.h"
#include "Map.h"

namespace Freeking
{
	BaseCastEntity::BaseCastEntity() :
		_frameTime(0),
		_animIndex(0),
		_frame(0),
		_nextFrame(0),
		_frameDelta(0)
	{
	}

	void BaseCastEntity::Initialize()
	{
		PrimitiveEntity::Initialize();

		static const std::array<std::string, 3> bodyParts =
		{
			"head",
			"body",
			"legs"
		};

		int bodyPartIndex = 0;
		for (const auto& bodyPart : bodyParts)
		{
			if (auto mesh = DynamicModel::Library.Get(_modelFolder + "/" + bodyPart + ".mdx"))
			{
				if (auto texture = Texture2D::Library.Get(_skinFolder[bodyPartIndex] + "/" + bodyPart + "_" + _artSkins[bodyPartIndex] + ".tga"))
				{
					_meshTextures.push_back(texture);
					_meshes.push_back(mesh);
				}
			}

			bodyPartIndex++;
		}

		if (!_meshes.empty())
		{
			std::string currentFrameName = "";
			size_t currentFrameIndex = 0;

			for (auto frameTransform : _meshes.front()->FrameTransforms)
			{
				auto indexStart = frameTransform.name.find_last_of('_');
				auto frameName = frameTransform.name.substr(0, indexStart);

				if (currentFrameName != frameName)
				{
					currentFrameName = frameName;
					_animFrameIndex.push_back({ currentFrameIndex, 0 });
				}

				auto& animFrameIndex = _animFrameIndex.back();
				animFrameIndex.numFrames += 1;

				currentFrameIndex++;
			}
		}

		_shader = Shader::Library.DynamicModel;

		SetLocalBounds(Vector3f(-16, -24, -16), Vector3f(16, 50, 16));
	}

	void BaseCastEntity::Tick(double dt)
	{
		PrimitiveEntity::Tick(dt);

		_animIndex = Math::Clamp(_animIndex, 0, (int)_animFrameIndex.size() - 1);

		auto animFrameIndex = _animFrameIndex[_animIndex];
		auto frameCount = animFrameIndex.numFrames;

		_frameTime += (10.0 * dt);
		_frameTime = fmod(_frameTime, (float)frameCount);

		_frame = (size_t)floor(_frameTime);
		_frame %= frameCount;
		_nextFrame = (_frame + 1) % frameCount;
		_frameDelta = (float)_frameTime - (float)_frame;

		_frame += animFrameIndex.firstFrame;
		_nextFrame += animFrameIndex.firstFrame;
		_frameDelta = Math::Clamp(_frameDelta, 0.0f, 1.0f);

		Vector3f traceStart = GetTransform().Translation() + Vector3f::Up * 70.0f;
		Vector3f traceEnd = Renderer::ViewMatrix.InverseTranslation();
		if (auto trace = Map::Current->LineTrace(traceStart, traceEnd, BspContentFlags::MaskOpaque);
			trace.hit == false)
		{
			auto traceDirection = traceEnd - traceStart;
			SetRotation(Quaternion::FromRadianYaw(atan2(traceDirection.x, traceDirection.z) - Math::HalfPi));
		}
	}

	void BaseCastEntity::PostTick()
	{
		PrimitiveEntity::PostTick();

		if (!_hidden && Renderer::DebugDraw)
		{
			const auto& viewMatrix = Renderer::ViewMatrix;
			auto position = GetTransformCenter().Translation();
			float distance = position.LengthBetween(viewMatrix.InverseTranslation());

			if (distance < 512.0f)
			{
				float alpha = 1.0f - (distance / 512.0f);

				for (const auto& mesh : _meshes)
				{
					const auto& frameTransform = mesh->FrameTransforms.at(_frame);
					const auto& nextFrameTransform = mesh->FrameTransforms.at(_nextFrame);
					auto boundsMin = Vector3f::Lerp(frameTransform.boundsMin, nextFrameTransform.boundsMin, _frameDelta);
					auto boundsMax = Vector3f::Lerp(frameTransform.boundsMax, nextFrameTransform.boundsMax, _frameDelta);
					
					LineRenderer::Debug->DrawBox(GetTransform(), boundsMin, boundsMax, LinearColor(0, 1, 1, alpha));
				}

				LineRenderer::Debug->DrawBox(GetTransform(), GetLocalMinBounds(), GetLocalMaxBounds(), LinearColor(0, 1, 0, alpha));
			}
		}
	}

	void BaseCastEntity::PreRender(bool translucent)
	{
		_shader->SetParameterValue("delta", _frameDelta);
		_shader->SetParameterValue("model", GetTransform());
		_shader->SetParameterValue("normalBuffer", DynamicModel::GetNormalBuffer().get());
	}

	void BaseCastEntity::RenderOpaque()
	{
		for (size_t i = 0; i < _meshes.size(); ++i)
		{
			const auto& mesh = _meshes.at(i);
			const auto& meshTexture = _meshTextures.at(i);

			_shader->SetParameterValue("diffuse", meshTexture.get());
			_shader->SetParameterValue("frameVertexBuffer", mesh->GetFrameVertexBuffer().get());
			_shader->SetParameterValue("frames[0].index", (int)(_frame * mesh->GetFrameVertexCount()));
			_shader->SetParameterValue("frames[0].translate", mesh->FrameTransforms[_frame].translate);
			_shader->SetParameterValue("frames[0].scale", mesh->FrameTransforms[_frame].scale);
			_shader->SetParameterValue("frames[1].index", (int)(_nextFrame * mesh->GetFrameVertexCount()));
			_shader->SetParameterValue("frames[1].translate", mesh->FrameTransforms[_nextFrame].translate);
			_shader->SetParameterValue("frames[1].scale", mesh->FrameTransforms[_nextFrame].scale);
			_shader->Apply();

			mesh->Draw();
		}
	}

	bool BaseCastEntity::SetProperty(const EntityProperty& property)
	{
		if (property.IsKey("art_skins"))
		{
			std::vector<std::string> artSkins;
			if (property.ValueAsStringArray(artSkins) && artSkins.size() == 3)
			{
				_artSkins[0] = artSkins[0];
				_artSkins[1] = artSkins[1];
				_artSkins[2] = artSkins[2];

				return true;
			}

			return false;
		}

		return PrimitiveEntity::SetProperty(property);
	}

	void BaseCastEntity::Trace(const Vector3f& start, const Vector3f& end, const Vector3f& mins, const Vector3f& maxs, TraceResult& trace, const BspContentFlags& brushMask)
	{
		if ( _hidden)
		{
			return;
		}
	}
}
