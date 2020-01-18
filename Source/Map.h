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

	class Map
	{
	public:

		Map(const BspFile& bspFile);

		void Render(const Matrix4x4& viewProjection);

		static std::shared_ptr<LightmapNode> ReadLightmap(LightmapImage& image, std::shared_ptr<LightmapNode>& root, int offset, int width, int height, const uint8_t* buffer);

		const std::vector<EntityLump::EntityDef>& Entities() const { return _entityLump->Entities; }

	private:

		std::map<std::string, std::unique_ptr<Mesh>> _meshes;
		std::shared_ptr<Texture2D> _lightmapTexture;
		std::map<std::string, std::shared_ptr<Texture2D>> _textures;
		std::shared_ptr<ShaderProgram> _shader;
		std::unique_ptr<EntityLump> _entityLump;
		std::shared_ptr<TextureSampler> _textureSampler;
		std::shared_ptr<TextureSampler> _lightmapSampler;
	};
}
