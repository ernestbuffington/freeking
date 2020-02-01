#pragma once

#include "DynamicModel.h"
#include "EntityLump.h"
#include "TextureSampler.h"
#include "Vector.h"
#include "Quaternion.h"
#include "PrimitiveEntity.h"
#include <string>
#include <memory>
#include <charconv>
#include <array>

namespace Freeking
{
	struct BspFile;

	class Map;
	class BrushModel;
	class LightmapNode;
	class LightmapImage;
	class Material;

	class BrushMesh
	{
	public:

		struct Vertex
		{
			Vector3f Position;
			Vector3f Normal;
			std::array<Vector2f, 3> UV;
		};

		BrushMesh() :
			AlphaCutOff(0.0f),
			AlphaMultiply(0.0f),
			Translucent(false)
		{
		}

		void Draw();
		void Commit();

		inline void SetDiffuse(const std::shared_ptr<Texture2D>& texture) { _diffuse = texture; }
		inline void SetLightmap(const std::shared_ptr<Texture2D>& texture) { _lightmap = texture; }

		inline const std::shared_ptr<Texture2D>& GetDiffuse() const { return _diffuse; }
		inline const std::shared_ptr<Texture2D>& GetLightmap() const { return _lightmap; }

		inline size_t GetNumVertices() const { return Vertices.size(); }
		inline size_t GetNumIndices() const { return Indices.size(); }

		std::vector<Vertex> Vertices;
		std::vector<uint32_t> Indices;

		float AlphaCutOff;
		float AlphaMultiply;
		bool Translucent;

	private:

		std::unique_ptr<VertexBinding> _vertexBinding;
		std::unique_ptr<VertexBuffer> _vertexBuffer;
		std::unique_ptr<IndexBuffer> _indexBuffer;
		std::shared_ptr<Texture2D> _diffuse;
		std::shared_ptr<Texture2D> _lightmap;
	};

	class BrushModel
	{
	public:

		void RenderOpaque(const Matrix4x4& viewProjection, const std::shared_ptr<Material>& material);
		void RenderTranslucent(const Matrix4x4& viewProjection, const std::shared_ptr<Material>& material);
		void RenderDebug(class LineRenderer* lineRenderer);

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
		void Render(const Matrix4x4& viewProjection, class LineRenderer* lineRenderer);

		const std::vector<EntityProperties>& GetEntityProperties() { return _entityKeyValues; }
		const std::shared_ptr<BrushModel>& GetBrushModel(uint32_t index) const { return _models.at(index); }

		static Map* Current;

	private:

		std::vector<std::shared_ptr<BrushModel>> _models;
		std::shared_ptr<Texture2D> _lightmapTexture;
		std::map<std::string, std::shared_ptr<Texture2D>> _textures;
		std::shared_ptr<Material> _material;
		std::vector<std::shared_ptr<BaseEntity>> _entities;
		std::vector<std::shared_ptr<PrimitiveEntity>> _worldEntities;
		std::vector<EntityProperties> _entityKeyValues;
	};
}
