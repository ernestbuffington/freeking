#include "Thug.h"
#include "MdxFile.h"
#include "Md2/Md2File.h"
#include "Util.h"
#include "FileSystem.h"
#include "Input.h"
#include "Material.h"
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
			auto mesh = DynamicModel::Library.Get("models/actors/" + actorName + "/" + bodyPart + ".mdx");
			if (mesh)
			{
				mesh->SetDiffuse(Texture2D::Library.Get("models/actors/" + skinFolder[bodyPartIndex] + "/" + bodyPart + "_" + artSkins[bodyPartIndex] + ".tga"));
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
					mesh->SetDiffuse(Texture2D::Library.Get(mesh->Skins[0]));
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

		auto shader = ShaderProgram::Library.Get("Shaders/DynamicModel.shader");
		_material = std::make_shared<Material>(shader);
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

		uint32_t frame = (uint32_t)floor(_frameTime);
		frame %= frameCount;
		uint32_t nextFrame = (frame + 1) % frameCount;
		float delta = (float)_frameTime - (float)frame;
		delta = Math::Clamp(delta, 0.0f, 1.0f);

		frame += animFrameIndex.firstFrame;
		nextFrame += animFrameIndex.firstFrame;

		_material->SetParameterValue("delta", delta);
		_material->SetParameterValue("viewProj", viewProjection * ModelMatrix);
		_material->SetParameterValue("normalBuffer", DynamicModel::GetNormalBuffer().get());

		for (const auto& mesh : _meshes)
		{
			_material->SetParameterValue("diffuse", mesh->GetDiffuse().get());
			_material->SetParameterValue("frameVertexBuffer", mesh->GetFrameVertexBuffer().get());
			_material->SetParameterValue("frames[0].index", (int)(frame * mesh->GetFrameVertexCount()));
			_material->SetParameterValue("frames[0].translate", mesh->FrameTransforms[frame].translate);
			_material->SetParameterValue("frames[0].scale", mesh->FrameTransforms[frame].scale);
			_material->SetParameterValue("frames[1].index", (int)(nextFrame * mesh->GetFrameVertexCount()));
			_material->SetParameterValue("frames[1].translate", mesh->FrameTransforms[nextFrame].translate);
			_material->SetParameterValue("frames[1].scale", mesh->FrameTransforms[nextFrame].scale);
			_material->Apply();

			mesh->Draw();
		}
	}
}
