#pragma once

#include "Mesh.h"
#include "EntityLump.h"
#include "TextureSampler.h"
#include <string>
#include <memory>

namespace Freeking
{
	struct BspFile;

	class LightmapNode;
	class LightmapImage;

	class BrushModel
	{
	public:

		std::map<std::string, std::shared_ptr<BrushMesh>> Meshes;
	};

	class Map
	{
	public:

		Map(const BspFile& bspFile);

		void Render(const Matrix4x4& viewProjection);

		const std::vector<EntityLump::EntityDef>& Entities() const { return _entityLump->Entities; }
		const std::shared_ptr<BrushModel>& GetBrushModel(uint32_t index) const { return _models.at(index); }

	private:

		std::vector<std::shared_ptr<BrushModel>> _models;
		std::shared_ptr<Texture2D> _lightmapTexture;
		std::map<std::string, std::shared_ptr<Texture2D>> _textures;
		std::shared_ptr<ShaderProgram> _shader;
		std::unique_ptr<EntityLump> _entityLump;
		std::shared_ptr<TextureSampler> _textureSampler;
		std::shared_ptr<TextureSampler> _lightmapSampler;
	};
}
