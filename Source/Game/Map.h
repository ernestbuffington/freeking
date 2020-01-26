#pragma once

#include "Mesh.h"
#include "EntityLump.h"
#include "TextureSampler.h"
#include "Vector.h"
#include "Quaternion.h"
#include "IEntity.h"
#include <string>
#include <memory>
#include <charconv>

namespace Freeking
{
	struct BspFile;

	class Map;
	class BrushModel;
	class LightmapNode;
	class LightmapImage;

	class BrushModel
	{
	public:

		void RenderOpaque(const Matrix4x4& viewProjection, const std::shared_ptr<ShaderProgram>& shader);
		void RenderTranslucent(const Matrix4x4& viewProjection, const std::shared_ptr<ShaderProgram>& shader);

		std::map<std::string, std::shared_ptr<BrushMesh>> Meshes;

		Vector3f BoundsMin;
		Vector3f BoundsMax;
		Vector3f Origin;
	};

	class Map
	{
	public:

		Map(const BspFile& bspFile);

		void Tick(double dt);
		void Render(const Matrix4x4& viewProjection);

		const std::vector<EntityLump::EntityDef>& Entities() const { return _entityLump->Entities; }
		const std::shared_ptr<BrushModel>& GetBrushModel(uint32_t index) const { return _models.at(index); }

		static Map* Current;

	private:

		std::vector<std::shared_ptr<BrushModel>> _models;
		std::shared_ptr<Texture2D> _lightmapTexture;
		std::map<std::string, std::shared_ptr<Texture2D>> _textures;
		std::shared_ptr<ShaderProgram> _shader;
		std::unique_ptr<EntityLump> _entityLump;
		std::shared_ptr<TextureSampler> _textureSampler;
		std::shared_ptr<TextureSampler> _lightmapSampler;
		std::vector<std::shared_ptr<IEntity>> _entities;
		std::vector<std::shared_ptr<BaseWorldEntity>> _worldEntities;
	};
}
