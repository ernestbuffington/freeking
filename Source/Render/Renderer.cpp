#include "Renderer.h"
#include "VertexBinding.h"
#include "Material.h"

namespace Freeking
{
	void Renderer::Draw(VertexBinding* binding, Material* material, DrawPrimitive primitive, int offset, int count, int instances)
	{
		if (material == nullptr || binding == nullptr)
		{
			return;
		}

		if (count == 0)
		{
			count = binding->GetNumElements();
		}

		_drawCalls.push_back(
			{ 
				binding,
				material,
				primitive,
				offset,
				count,
				instances
			});
	}

	static inline GLenum GLDrawPrimitive(DrawPrimitive e)
	{
		switch (e)
		{
		case DrawPrimitive::Triangles: return GL_TRIANGLES;
		case DrawPrimitive::Lines: return GL_LINES;
		}

		return GL_INVALID_ENUM;
	}

	void Renderer::Flush()
	{
		for (auto& drawCall : _drawCalls)
		{
			auto mode = GLDrawPrimitive(drawCall.primitive);
			if (mode == GL_INVALID_ENUM)
			{
				continue;
			}

			drawCall.material->Apply();
			drawCall.binding->Bind();

			if (drawCall.binding->HasIndices())
			{
				GLenum indexType = static_cast<GLenum>(drawCall.binding->GetIndexType());

				if (drawCall.offset > 0)
				{
					if (drawCall.instances > 1)
					{
						glDrawElementsInstancedBaseVertex(mode, drawCall.count, indexType, nullptr, drawCall.instances, drawCall.offset);
					}
					else
					{
						glDrawElementsBaseVertex(mode, drawCall.count, indexType, nullptr, drawCall.offset);
					}
				}
				else
				{
					if (drawCall.instances > 1)
					{
						glDrawElementsInstanced(mode, drawCall.count, indexType, nullptr, drawCall.instances);
					}
					else
					{
						glDrawElements(mode, drawCall.count, indexType, nullptr);
					}
				}
			}
			else
			{
				if (drawCall.instances > 1)
				{
					glDrawArraysInstanced(mode, drawCall.offset, drawCall.count, drawCall.instances);
				}
				else
				{
					glDrawArrays(mode, drawCall.offset, drawCall.count);
				}
			}

			drawCall.binding->Unbind();
			drawCall.material->Unbind();
		}

		_drawCalls.clear();
	}
}
