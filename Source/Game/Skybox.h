#pragma once

#include <string>
#include <memory>

namespace Freeking
{
	class VertexBinding;
	class VertexBuffer;
	class IndexBuffer;
	class TextureCube;
	class TextureSampler;
	class Shader;
	class Matrix4x4;

	class Skybox
	{
	public:

		Skybox() = delete;
		Skybox(const std::string& name);

		void Draw();

		TextureCube* GetCubemap() { return _cubemap.get(); }

	private:

		std::unique_ptr<VertexBinding> _vertexBinding;
		std::unique_ptr<VertexBuffer> _vertexBuffer;
		std::unique_ptr<IndexBuffer> _indexBuffer;
		std::shared_ptr<TextureCube> _cubemap;
		std::shared_ptr<TextureSampler> _cubemapSampler;
		std::shared_ptr<Shader> _shader;
		int _cubemapParameterId;
	};
}
