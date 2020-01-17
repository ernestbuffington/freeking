#include "Thug.h"
#include "MdxFile.h"
#include "Util.h"
#include "FileSystem.h"

namespace Freeking
{
	Thug::Thug() :
		_frameTime(0.0)
	{
		static const std::array<std::string, 3> bodyParts =
		{
			"body",
			"head",
			"legs",
		};

		for (const auto& bodyPart : bodyParts)
		{
			auto mdxBuffer = FileSystem::GetFileData("models/actors/thug/" + bodyPart + ".mdx");
			auto mdxData = mdxBuffer.data();
			auto& mdxFile = MDXFile::Create(mdxData);

			auto mesh = std::make_shared<KeyframeMesh>();
			mdxFile.Build(mdxData, mesh);
			mesh->SetDiffuse(Util::LoadTexture("models/actors/thug/" + bodyPart + "_001.tga"));
			mesh->Commit();

			_meshes.push_back(mesh);
		}

		_shader = Util::LoadShader("Shaders/VertexSkinnedMesh.vert", "Shaders/VertexSkinnedMesh.frag");
	}

	void Thug::Render(const Matrix4x4& viewProjection, double dt)
	{
		_shader->Bind();
		_shader->SetUniformValue("diffuse", 0);
		_shader->SetUniformValue("frameVertexBuffer", 1);
		_shader->SetUniformValue("normalBuffer", 2);

		auto frameCount = _meshes.at(0)->GetFrameCount();
		_frameTime += (10.0 * dt);
		_frameTime = fmod(_frameTime, (float)frameCount);

		uint32_t frame = (uint32_t)floor(_frameTime);
		frame %= frameCount;
		uint32_t nextFrame = (frame + 1) % frameCount;
		float delta = (float)_frameTime - (float)frame;
		delta = Math::Clamp(delta, 0.0f, 1.0f);

		_shader->SetUniformValue("delta", delta);
		_shader->SetUniformValue("viewProj", viewProjection);

		for (const auto& mesh : _meshes)
		{
			_shader->SetUniformValue("frames[0].index", (int)(frame * mesh->GetFrameVertexCount()));
			_shader->SetUniformValue("frames[0].translate", mesh->FrameTransforms[frame].translate);
			_shader->SetUniformValue("frames[0].scale", mesh->FrameTransforms[frame].scale);

			_shader->SetUniformValue("frames[1].index", (int)(nextFrame * mesh->GetFrameVertexCount()));
			_shader->SetUniformValue("frames[1].translate", mesh->FrameTransforms[nextFrame].translate);
			_shader->SetUniformValue("frames[1].scale", mesh->FrameTransforms[nextFrame].scale);

			mesh->Draw();
		}
	}
}
