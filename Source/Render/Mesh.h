#pragma once

#include "Vector.h"
#include "VertexBinding.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "TextureBuffer.h"
#include "Texture2D.h"
#include "ShaderProgram.h"
#include <vector>
#include <memory>

namespace Freeking
{
	class BrushMesh
	{
	public:

		struct Vertex
		{
			Vector3f Position;
			Vector3f Normal;
			Vector2f UV[3];
		};

		void Draw();
		void Commit();
		inline void SetDiffuse(const std::shared_ptr<Texture2D>& texture) { _diffuse = texture; }
		inline void SetLightmap(const std::shared_ptr<Texture2D>& texture) { _lightmap = texture; }

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

	class KeyframeMesh
	{
	public:

		struct Vertex
		{
			Vector2f UV;
			int VertexIndex;
		};

		struct FrameVertex
		{
			int8_t x, y, z, n;
		};

		struct FrameTransform
		{
			std::string name;
			Vector3f translate;
			Vector3f scale;
		};

		void Draw();
		void Commit();
		void SetDiffuse(const std::shared_ptr<Texture2D>& texture);

		inline uint32_t GetFrameCount() const { return _frameCount; }
		inline uint32_t GetFrameVertexCount() const { return _frameVertexCount; }
		inline void SetFrameCount(uint32_t frameCount) { _frameCount = frameCount; }
		inline void SetFrameVertexCount(uint32_t frameVertexCount) { _frameVertexCount = frameVertexCount; }

		std::vector<Vertex> Vertices;
		std::vector<uint32_t> Indices;
		std::vector<FrameVertex> FrameVertices;
		std::vector<FrameTransform> FrameTransforms;
		std::vector<std::string> Skins;

	private:

		uint32_t _frameCount;
		uint32_t _frameVertexCount;
		std::unique_ptr<VertexBinding> _vertexBinding;
		std::unique_ptr<VertexBuffer> _vertexBuffer;
		std::unique_ptr<IndexBuffer> _indexBuffer;
		std::shared_ptr<TextureBuffer> _frameVertexBuffer;
		std::shared_ptr<TextureBuffer> _normalBuffer;
		std::shared_ptr<Texture2D> _diffuse;
	};
}
