#pragma once

#include "AssetLibrary.h"
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
	class DynamicModel;

	class DynamicModelLibrary : public AssetLibrary<DynamicModel>
	{
	protected:

		virtual void UpdateLoaders() override;
	};

	class DynamicModel
	{
	public:

		static DynamicModelLibrary Library;

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

		inline uint32_t GetFrameCount() const { return _frameCount; }
		inline uint32_t GetFrameVertexCount() const { return _frameVertexCount; }
		inline void SetFrameCount(uint32_t frameCount) { _frameCount = frameCount; }
		inline void SetFrameVertexCount(uint32_t frameVertexCount) { _frameVertexCount = frameVertexCount; }

		inline const std::unique_ptr<VertexBinding>& GetBinding() const { return _vertexBinding; }
		inline const std::shared_ptr<TextureBuffer>& GetFrameVertexBuffer() const { return _frameVertexBuffer; }
		static const std::unique_ptr<TextureBuffer>& GetNormalBuffer();

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
	};
}
