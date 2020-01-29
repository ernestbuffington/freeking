#pragma once

#include "DynamicModel.h"
#include "EntityLump.h"
#include <unordered_map>

namespace Freeking
{
	class Material;

	class Thug
	{
	public:

		Thug(const EntityLump::EntityDef& entityDef);

		void Render(const Matrix4x4& viewProjection, double dt);

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
		std::shared_ptr<Material> _material;
		double _frameTime;
		int _animIndex;
	};
}
