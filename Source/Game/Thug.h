#pragma once

#include "DynamicModel.h"
#include "EntityLump.h"
#include <unordered_map>

namespace Freeking
{
	class Shader;

	class Thug
	{
	public:

		Thug(const EntityProperties& entityKeyValues);

		void Render(double dt);

		Matrix4x4 ModelMatrix;

	private:

		struct AnimFrameIndex
		{
			size_t firstFrame;
			size_t numFrames;
		};

		std::vector<std::shared_ptr<DynamicModel>> _meshes;
		std::vector<std::shared_ptr<Texture2D>> _meshTextures;
		std::vector<AnimFrameIndex> _animFrameIndex;
		std::shared_ptr<Shader> _shader;
		double _frameTime;
		int _animIndex;
	};
}
