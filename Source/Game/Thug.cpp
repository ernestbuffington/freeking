#include "Thug.h"
#include "MdxFile.h"
#include "Md2/Md2File.h"
#include "Util.h"
#include "FileSystem.h"
#include "Input.h"
#include "Shader.h"
#include <charconv>

namespace Freeking
{
	Thug::Thug(const EntityProperties& entityKeyValues) :
		_frameTime(0.0),
		_animIndex(0)
	{
		auto actorName = (*entityKeyValues.GetClassnameProperty()).substr(5);

		static const std::array<std::string, 3> bodyParts =
		{
			"head",
			"body",
			"legs"
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
		entityKeyValues.TryGetSplitString("art_skins", artSkins);

		int bodyPartIndex = 0;
		for (const auto& bodyPart : bodyParts)
		{
			auto mesh = DynamicModel::Library.Get("models/actors/" + actorName + "/" + bodyPart + ".mdx");
			if (mesh)
			{
				_meshTextures.push_back(Texture2D::Library.Get("models/actors/" + skinFolder[bodyPartIndex] + "/" + bodyPart + "_" + artSkins[bodyPartIndex] + ".tga"));
				_meshes.push_back(mesh);
			}

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
				auto mesh = DynamicModel::Library.Get("models/actors/" + actorName + "/" + attachment + ".mdx");
				if (mesh)
				{
					_meshTextures.push_back(Texture2D::Library.Get(mesh->Skins[0]));
					_meshes.push_back(mesh);
				}
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

		_shader = Shader::Library.Get("Shaders/DynamicModel.shader");
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

		auto animFrameIndex = _animFrameIndex[_animIndex];
		auto frameCount = animFrameIndex.numFrames;
		_frameTime += (10.0 * dt);
		_frameTime = fmod(_frameTime, (float)frameCount);

		size_t frame = (size_t)floor(_frameTime);
		frame %= frameCount;
		size_t nextFrame = (frame + 1) % frameCount;
		float delta = (float)_frameTime - (float)frame;
		delta = Math::Clamp(delta, 0.0f, 1.0f);

		frame += animFrameIndex.firstFrame;
		nextFrame += animFrameIndex.firstFrame;

		_shader->SetParameterValue("delta", delta);
		_shader->SetParameterValue("viewProj", viewProjection * ModelMatrix);
		_shader->SetParameterValue("normalBuffer", DynamicModel::GetNormalBuffer().get());

		for (auto i = 0; i < _meshes.size(); ++i)
		{
			auto& mesh = _meshes.at(i);
			auto& meshTexture = _meshTextures.at(i);
			_shader->SetParameterValue("diffuse", meshTexture.get());
			_shader->SetParameterValue("frameVertexBuffer", mesh->GetFrameVertexBuffer().get());
			_shader->SetParameterValue("frames[0].index", (int)(frame * mesh->GetFrameVertexCount()));
			_shader->SetParameterValue("frames[0].translate", mesh->FrameTransforms[frame].translate);
			_shader->SetParameterValue("frames[0].scale", mesh->FrameTransforms[frame].scale);
			_shader->SetParameterValue("frames[1].index", (int)(nextFrame * mesh->GetFrameVertexCount()));
			_shader->SetParameterValue("frames[1].translate", mesh->FrameTransforms[nextFrame].translate);
			_shader->SetParameterValue("frames[1].scale", mesh->FrameTransforms[nextFrame].scale);
			_shader->Apply();

			mesh->Draw();
		}
	}
}
