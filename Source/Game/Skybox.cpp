#include "Skybox.h"
#include "TextureCube.h"
#include "TextureSampler.h"
#include "VertexBinding.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Matrix4x4.h"
#include "stb_image.h"

namespace Freeking
{
	Skybox::Skybox(const std::string& name)
	{
		if (_cubemap = TextureCube::Library.Get(name);
			_cubemap == nullptr)
		{
			std::array<TextureCube::Image, 6> faces;
			static const std::string sides[6] = { "ft", "bk", "up", "dn", "rt", "lf" };

			for (int i = 0; i < 6; ++i)
			{
				auto& face = faces[i];
				const auto& side = sides[i];
				auto filename = "env/" + name + side;

				auto buffer = FileSystem::GetFileData(filename + ".tga");
				if (buffer.empty()) buffer = FileSystem::GetFileData(filename + ".TGA");
				if (!buffer.empty())
				{
					int imageWidth, imageHeight, imageChannels;
					if (uint8_t* image = stbi_load_from_memory(
						(uint8_t*)buffer.data(), (std::int32_t)buffer.size(),
						&imageWidth, &imageHeight, &imageChannels, 0))
					{
						face.width = imageWidth;
						face.height = imageHeight;
						face.internalFormat = GL_RGBA8;
						face.format = imageChannels == 3 ? GL_RGB : GL_RGBA;
						face.type = GL_UNSIGNED_BYTE;
						face.data.assign(image, image + (imageWidth * imageHeight) * imageChannels);

						stbi_image_free(image);
					}
				}
			}

			_cubemap = std::make_shared<TextureCube>(faces);

			TextureCube::Library.SetSpecialNamed(name, _cubemap);
		}

		static const float vertices[] =
		{
			-1, -1, -1,
			1, -1, -1,
			1, 1, -1,
			-1, 1, -1,
			-1, -1, 1,
			1, -1, 1,
			1, 1, 1,
			-1, 1, 1
		};

		static const uint32_t indices[] =
		{
			0, 1, 3, 3, 1, 2,
			1, 5, 2, 2, 5, 6,
			5, 4, 6, 6, 4, 7,
			4, 0, 7, 7, 0, 3,
			3, 2, 7, 7, 2, 6,
			4, 5, 0, 0, 5, 1
		};

		_vertexBuffer = std::make_unique<VertexBuffer>(vertices, 8, 12, GL_STATIC_DRAW);
		_indexBuffer = std::make_unique<IndexBuffer>(indices, 36, GL_UNSIGNED_INT);

		ArrayElement vertexLayout[] =
		{
			ArrayElement(_vertexBuffer.get(), 0, 3, ElementType::Float, 12, 0),
		};

		_vertexBinding = std::make_unique<VertexBinding>();
		_vertexBinding->Create(vertexLayout, 1, *_indexBuffer, ElementType::UInt);

		_shader = Shader::Library.Skybox;
	}

	void Skybox::Draw()
	{
		_shader->Bind();
		_shader->SetParameterValue(
			"cubemap",
			_cubemap.get(),
			TextureSampler::Library.Get({ TextureWrapMode::ClampEdge, TextureFilterMode::Linear }).get());

		_vertexBinding->Bind();
		glDrawElements(GL_TRIANGLES, _vertexBinding->GetNumElements(), GL_UNSIGNED_INT, (void*)0);
		_vertexBinding->Unbind();

		_shader->Unbind();
	}
}
