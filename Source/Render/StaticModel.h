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
	class StaticModel;

	class StaticModelLibrary : public AssetLibrary<StaticModel>
	{
	protected:

		virtual void UpdateLoaders() override;
	};

	class StaticModel
	{
	public:

		static StaticModelLibrary Library;

		struct Vertex
		{
			Vector3f Position;
			Vector3f Normal;
			Vector2f UV;
		};

		void Commit();

		std::vector<Vertex> Vertices;
		std::vector<uint32_t> Indices;

	private:

		std::unique_ptr<VertexBinding> _vertexBinding;
		std::unique_ptr<VertexBuffer> _vertexBuffer;
		std::unique_ptr<IndexBuffer> _indexBuffer;
	};
}
