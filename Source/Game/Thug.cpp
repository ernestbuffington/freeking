#include "Thug.h"
#include "MdxFile.h"
#include "Util.h"
#include "FileSystem.h"
#include "Input.h"
#include <charconv>

namespace Freeking
{
	Thug::Thug(const EntityLump::EntityDef& entityDef) :
		_frameTime(0.0),
		_animIndex(0)
	{
		auto actorName = entityDef.classname.substr(5);

		static const std::array<std::string, 3> bodyParts =
		{
			"head",
			"body",
			"legs",
		};

		static std::unordered_map<std::string, std::array<std::string, 3>> skinFolders =
		{
			{"bitch", {"bitch", "bitch", "bitch"}},
			{"bum_sit", {"thug", "thug", "thug"}},
			{"punk", {"thug", "thug", "thug"}},
			{"runt", {"runt", "runt", "thug"}},
			{"shorty", {"thug", "thug", "thug"}},
			{"thug", {"thug", "thug", "thug"}},
			{"thug_sit", {"thug", "thug", "thug"}},
			{"whore", {"bitch", "bitch", "bitch"}},
		};

		const auto& skinFolder = skinFolders[actorName];

		std::vector<std::string> artSkins;
		entityDef.TryGetSplitString("art_skins", artSkins);

		int bodyPartIndex = 0;
		for (const auto& bodyPart : bodyParts)
		{
			auto mdxBuffer = FileSystem::GetFileData("models/actors/" + actorName + "/" + bodyPart + ".mdx");
			auto& mdxFile = MDXFile::Create(mdxBuffer.data());
			auto mesh = std::make_shared<KeyframeMesh>();
			mdxFile.Build(mesh);
			mesh->SetDiffuse(Util::LoadTexture("models/actors/" + skinFolder[bodyPartIndex] + "/" + bodyPart + "_" + artSkins[bodyPartIndex] + ".tga"));
			mesh->Commit();

			_meshes.push_back(mesh);

			bodyPartIndex++;
		}

		if (actorName == "runt")
		{
			static const std::array<std::string, 3> attachments =
			{
				"cigar",
				"fedora",
				"pipe"
			};

			for (const auto& attachment : attachments)
			{
				auto mdxBuffer = FileSystem::GetFileData("models/actors/" + actorName + "/" + attachment + ".mdx");
				if (mdxBuffer.empty())
				{
					continue;
				}

				auto& mdxFile = MDXFile::Create(mdxBuffer.data());
				auto mesh = std::make_shared<KeyframeMesh>();
				mdxFile.Build(mesh);
				mesh->SetDiffuse(Util::LoadTexture(mesh->Skins[0]));
				mesh->Commit();

				_meshes.push_back(mesh);
			}
		}

		std::string currentFrameName = "";
		size_t currentFrameIndex = 0;

		for (auto frameTransform : _meshes[0]->FrameTransforms)
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

		_shader = Util::LoadShader("Shaders/VertexSkinnedMesh.vert", "Shaders/VertexSkinnedMesh.frag");
	}

	void Thug::Render(const Matrix4x4& viewProjection, double dt)
	{
		if (Input::JustPressed(Button::KeyLeft))
		{
			_animIndex--;
		}
		else if (Input::JustPressed(Button::KeyRight))
		{
			_animIndex++;
		}

		_animIndex = Math::Clamp(_animIndex, 0, (int)_animFrameIndex.size() - 1);

		_shader->Bind();
		_shader->SetUniformValue("diffuse", 0);
		_shader->SetUniformValue("frameVertexBuffer", 1);
		_shader->SetUniformValue("normalBuffer", 2);

		auto animFrameIndex = _animFrameIndex[_animIndex];
		auto frameCount = animFrameIndex.numFrames;
		_frameTime += (10.0 * dt);
		_frameTime = fmod(_frameTime, (float)frameCount);

		uint32_t frame = (uint32_t)floor(_frameTime);
		frame %= frameCount;
		uint32_t nextFrame = (frame + 1) % frameCount;
		float delta = (float)_frameTime - (float)frame;
		delta = Math::Clamp(delta, 0.0f, 1.0f);

		frame += animFrameIndex.firstFrame;
		nextFrame += animFrameIndex.firstFrame;

		_shader->SetUniformValue("delta", delta);
		_shader->SetUniformValue("viewProj", viewProjection * ModelMatrix);

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
