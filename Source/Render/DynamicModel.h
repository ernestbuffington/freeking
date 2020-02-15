#pragma once

#include "AssetLibrary.h"
#include "Vector.h"
#include "VertexBinding.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "TextureBuffer.h"
#include "Texture2D.h"
#include "Shader.h"
#include "Util.h"
#include <vector>
#include <memory>

namespace Freeking
{
	class DynamicModel;

	struct FrameAnimation
	{
		std::string name;
		size_t firstFrame;
		size_t numFrames;
	};

	class FrameAnimator
	{
	public:

		FrameAnimator() :
			_playTime(0),
			_frame(0),
			_nextFrame(0),
			_frameDelta(0),
			_currentAnimation(0)
		{
		}

		void Tick(double dt)
		{
			const auto& animation = _animations.at(_currentAnimation);
			auto frameCount = animation.numFrames;

			_playTime += (10.0 * dt);
			_playTime = fmod(_playTime, (float)frameCount);

			_frame = (size_t)floor(_playTime);
			_frame %= frameCount;
			_nextFrame = (_frame + 1) % frameCount;
			_frameDelta = (float)_playTime - (float)_frame;

			_frame += animation.firstFrame;
			_nextFrame += animation.firstFrame;
			_frameDelta = Math::Clamp(_frameDelta, 0.0f, 1.0f);
		}

		void AddAnimation(const std::string& name, size_t firstFrame, size_t numFrames)
		{
			_animations.push_back({ name, firstFrame, numFrames });
		}

		void SetAnimation(size_t index)
		{
			_currentAnimation = index;
			_playTime = 0;
			_frame = 0;
			_nextFrame = 0;
			_frameDelta = 0;
		}

		inline double GetPlayTime() const { return _playTime; }
		inline size_t GetFrame() const { return _frame; }
		inline size_t GetNextFrame() const { return _nextFrame; }
		inline float GetFrameDelta() const { return _frameDelta; }
		inline size_t GetCurrentAnimation() const { return _currentAnimation; }

	private:

		std::vector<FrameAnimation> _animations;

		double _playTime;
		size_t _frame;
		size_t _nextFrame;
		float _frameDelta;
		size_t _currentAnimation;
	};

	class DynamicModelLibrary : public AssetLibrary<DynamicModel>
	{
	protected:

		virtual void UpdateLoaders() override;
	};

	class DynamicModel
	{
	public:

		static DynamicModelLibrary Library;

		struct Vertex
		{
			Vector2f UV;
			int VertexIndex;
		};

		struct FrameVertex
		{
			int8_t x, y, z, n;
		};

		struct FrameTransform
		{
			std::string name;
			Vector3f translate;
			Vector3f scale;
			Vector3f boundsMin;
			Vector3f boundsMax;
		};

		void Draw();
		void Commit();

		inline uint32_t GetFrameCount() const { return _frameCount; }
		inline uint32_t GetFrameVertexCount() const { return _frameVertexCount; }
		inline void SetFrameCount(uint32_t frameCount) { _frameCount = frameCount; }
		inline void SetFrameVertexCount(uint32_t frameVertexCount) { _frameVertexCount = frameVertexCount; }

		inline const std::unique_ptr<VertexBinding>& GetBinding() const { return _vertexBinding; }
		inline const std::shared_ptr<TextureBuffer>& GetFrameVertexBuffer() const { return _frameVertexBuffer; }
		static const std::unique_ptr<TextureBuffer>& GetNormalBuffer();

		std::vector<FrameAnimation> GetFrameAnimations() const;

		std::vector<Vertex> Vertices;
		std::vector<uint32_t> Indices;
		std::vector<FrameVertex> FrameVertices;
		std::vector<FrameTransform> FrameTransforms;
		std::vector<std::string> Skins;

	private:

		uint32_t _frameCount;
		uint32_t _frameVertexCount;
		std::unique_ptr<VertexBinding> _vertexBinding;
		std::unique_ptr<VertexBuffer> _vertexBuffer;
		std::unique_ptr<IndexBuffer> _indexBuffer;
		std::shared_ptr<TextureBuffer> _frameVertexBuffer;
	};
}
