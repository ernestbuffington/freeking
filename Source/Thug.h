#pragma once

#include "Mesh.h"

namespace Freeking
{
	class ShaderProgram;

	class Thug
	{
	public:

		Thug();

		void Render(const Matrix4x4& viewProjection, double dt);

	private:

		std::vector<std::shared_ptr<KeyframeMesh>> _meshes;
		std::shared_ptr<ShaderProgram> _shader;
		double _frameTime;
	};
}
