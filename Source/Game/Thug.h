#pragma once

#include "Mesh.h"
#include "EntityLump.h"
#include <unordered_map>

namespace Freeking
{
	class ShaderProgram;

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

		std::vector<std::shared_ptr<KeyframeMesh>> _meshes;
		std::vector<AnimFrameIndex> _animFrameIndex;
		std::shared_ptr<ShaderProgram> _shader;
		double _frameTime;
		int _animIndex;
	};
}
