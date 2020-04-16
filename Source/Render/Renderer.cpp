#include "Renderer.h"
#include "VertexBinding.h"
#include "Shader.h"

namespace Freeking
{
	Matrix4x4 Renderer::ProjectionMatrix;
	Matrix4x4 Renderer::ViewMatrix;
	float Renderer::ViewportWidth;
	float Renderer::ViewportHeight;
	bool Renderer::DebugDraw = true;

	static inline GLenum GLDrawPrimitive(DrawPrimitive e)
	{
		switch (e)
		{
		case DrawPrimitive::Triangles: return GL_TRIANGLES;
		case DrawPrimitive::Lines: return GL_LINES;
		}

		return GL_INVALID_ENUM;
	}

	void Renderer::Draw(VertexBinding* binding, Shader* shader, DrawPrimitive primitive, int offset, int count, int instances)
	{
		auto mode = GLDrawPrimitive(primitive);
		if (mode == GL_INVALID_ENUM)
		{
			return;
		}

		shader->Bind();
		binding->Bind();

		if (binding->HasIndices())
		{
			GLenum indexType = static_cast<GLenum>(binding->GetIndexType());

			if (offset > 0)
			{
				if (instances > 1)
				{
					glDrawElementsInstancedBaseVertex(mode, count, indexType, nullptr, instances, offset);
				}
				else
				{
					glDrawElementsBaseVertex(mode, count, indexType, nullptr, offset);
				}
			}
			else
			{
				if (instances > 1)
				{
					glDrawElementsInstanced(mode, count, indexType, nullptr, instances);
				}
				else
				{
					glDrawElements(mode, count, indexType, nullptr);
				}
			}
		}
		else
		{
			if (instances > 1)
			{
				glDrawArraysInstanced(mode, offset, count, instances);
			}
			else
			{
				glDrawArrays(mode, offset, count);
			}
		}

		binding->Unbind();
		shader->Unbind();
	}
}
