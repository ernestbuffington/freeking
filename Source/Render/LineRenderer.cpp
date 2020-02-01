#include "LineRenderer.h"
#include "Shader.h"
#include "Material.h"

namespace Freeking
{
	LineRenderer::LineRenderer(size_t maxVertexCount) :
		_maxVertexCount(maxVertexCount),
		_vertexCount(0)
	{
		_buffer.resize(VertexSize * _maxVertexCount, 0);

		_vertexBuffer = std::make_unique<VertexBuffer>(nullptr, _maxVertexCount, VertexSize, GL_DYNAMIC_DRAW);

		ArrayElement vertexLayout[] =
		{
			ArrayElement(_vertexBuffer.get(), 0, 3, ElementType::Float, VertexSize, 0),
			ArrayElement(_vertexBuffer.get(), 1, 4, ElementType::Float, VertexSize, 3 * sizeof(float))
		};

		_vertexBinding = std::make_unique<VertexBinding>();
		_vertexBinding->Create(vertexLayout, 2, *_vertexBuffer);

		_material = std::make_shared<Material>(Shader::Library.Get("Shaders/DebugLine.shader"));
	}

	void LineRenderer::Flush(Matrix4x4& viewProj)
	{
		if (_vertexCount < 2)
		{
			return;
		}

		_vertexBuffer->UpdateBuffer(_buffer.data(), 0, _vertexCount * VertexSize);

		_material->SetParameterValue("viewProj", viewProj);
		_material->Apply();

		_vertexBinding->Bind();
		glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(_vertexCount));
		_vertexBinding->Unbind();

		_vertexCount = 0;

		_material->Unbind();
	}

	void LineRenderer::DrawLine(const Vector3f& p1, const Vector3f& p2, const Vector4f& colour)
	{
		BufferVertex(p1, colour);
		BufferVertex(p2, colour);
	}

	void LineRenderer::DrawBox(const Matrix4x4& transform, const Vector3f& mins, const Vector3f& maxs, const Vector4f& colour)
	{
		DrawLine(transform * Vector3f(mins.x, mins.y, mins.z), transform * Vector3f(maxs.x, mins.y, mins.z), colour);
		DrawLine(transform * Vector3f(maxs.x, mins.y, mins.z), transform * Vector3f(maxs.x, maxs.y, mins.z), colour);
		DrawLine(transform * Vector3f(maxs.x, maxs.y, mins.z), transform * Vector3f(mins.x, maxs.y, mins.z), colour);
		DrawLine(transform * Vector3f(mins.x, maxs.y, mins.z), transform * Vector3f(mins.x, mins.y, mins.z), colour);
		DrawLine(transform * Vector3f(mins.x, mins.y, mins.z), transform * Vector3f(mins.x, mins.y, maxs.z), colour);
		DrawLine(transform * Vector3f(maxs.x, mins.y, mins.z), transform * Vector3f(maxs.x, mins.y, maxs.z), colour);
		DrawLine(transform * Vector3f(maxs.x, maxs.y, mins.z), transform * Vector3f(maxs.x, maxs.y, maxs.z), colour);
		DrawLine(transform * Vector3f(mins.x, maxs.y, mins.z), transform * Vector3f(mins.x, maxs.y, maxs.z), colour);
		DrawLine(transform * Vector3f(mins.x, mins.y, maxs.z), transform * Vector3f(maxs.x, mins.y, maxs.z), colour);
		DrawLine(transform * Vector3f(maxs.x, mins.y, maxs.z), transform * Vector3f(maxs.x, maxs.y, maxs.z), colour);
		DrawLine(transform * Vector3f(maxs.x, maxs.y, maxs.z), transform * Vector3f(mins.x, maxs.y, maxs.z), colour);
		DrawLine(transform * Vector3f(mins.x, maxs.y, maxs.z), transform * Vector3f(mins.x, mins.y, maxs.z), colour);
	}

	void LineRenderer::DrawAABBox(const Vector3f& position, const Vector3f& mins, const Vector3f& maxs, const Vector4f& colour)
	{
		DrawAABBox(position + mins, position + maxs, colour);
	}

	void LineRenderer::DrawAABBox(const Vector3f& mins, const Vector3f& maxs, const Vector4f& colour)
	{
		DrawLine(Vector3f(mins.x, mins.y, mins.z), Vector3f(maxs.x, mins.y, mins.z), colour);
		DrawLine(Vector3f(maxs.x, mins.y, mins.z), Vector3f(maxs.x, maxs.y, mins.z), colour);
		DrawLine(Vector3f(maxs.x, maxs.y, mins.z), Vector3f(mins.x, maxs.y, mins.z), colour);
		DrawLine(Vector3f(mins.x, maxs.y, mins.z), Vector3f(mins.x, mins.y, mins.z), colour);
		DrawLine(Vector3f(mins.x, mins.y, mins.z), Vector3f(mins.x, mins.y, maxs.z), colour);
		DrawLine(Vector3f(maxs.x, mins.y, mins.z), Vector3f(maxs.x, mins.y, maxs.z), colour);
		DrawLine(Vector3f(maxs.x, maxs.y, mins.z), Vector3f(maxs.x, maxs.y, maxs.z), colour);
		DrawLine(Vector3f(mins.x, maxs.y, mins.z), Vector3f(mins.x, maxs.y, maxs.z), colour);
		DrawLine(Vector3f(mins.x, mins.y, maxs.z), Vector3f(maxs.x, mins.y, maxs.z), colour);
		DrawLine(Vector3f(maxs.x, mins.y, maxs.z), Vector3f(maxs.x, maxs.y, maxs.z), colour);
		DrawLine(Vector3f(maxs.x, maxs.y, maxs.z), Vector3f(mins.x, maxs.y, maxs.z), colour);
		DrawLine(Vector3f(mins.x, maxs.y, maxs.z), Vector3f(mins.x, mins.y, maxs.z), colour);
	}

	void LineRenderer::DrawSphere(const Vector3f& position, float radius, int thetaSegments, int phiSegments, const Vector4f& colour)
	{
		int theta = thetaSegments + 1;
		int phi = phiSegments;

		std::vector<Vector3f> vertices;
		vertices.reserve(phi * theta);

		for (int i = 0; i < phi; ++i)
		{
			for (int j = 0; j < theta; ++j)
			{
				float u = j / (float)(theta - 1);
				float v = i / (float)(phi - 1);
				float t = Math::TwoPi * u;
				float p = Math::Pi * v;

				Vector3f vertex(
					radius * sin(p) * cos(t),
					radius * cos(p),
					radius * sin(p) * sin(t));

				vertex += position;

				vertices.push_back(vertex);
			}
		}

		for (int i = 0; i < phi - 1; ++i)
		{
			for (int j = 0; j < theta - 1; ++j)
			{
				int index = theta * i + j;

				DrawLine(vertices[index], vertices[index + theta], colour);
				DrawLine(vertices[index], vertices[index + 1], colour);
			}
		}
	}

	void LineRenderer::DrawCone(const Vector3f& position, float radius, float height, std::size_t sides, const Vector4f& colour)
	{
		if (sides < 3)
		{
			return;
		}

		std::vector<Vector3f> vertices;
		vertices.reserve(sides + 1);

		Vector3f topVertex = position + (Vector3f(0, 1, 0) * height);

		for (std::size_t i = 0; i <= sides; ++i)
		{
			float r = Math::TwoPi * (i / (float)sides);
			Vector3f vertex(radius * cos(r), 0.0f, radius * sin(r));
			vertices.push_back(position + vertex);
		}

		for (std::size_t i = 0; i < sides; ++i)
		{
			DrawLine(vertices[i], vertices[i + 1], colour);
			DrawLine(vertices[i], topVertex, colour);
		}
	}

	void LineRenderer::DrawCone(const Vector3f& position, const Quaternion& rotation, float radius, float height, std::size_t sides, const Vector4f& colour)
	{
		if (sides < 3)
		{
			return;
		}

		std::vector<Vector3f> vertices;
		vertices.reserve(sides + 1);

		Vector3f topVertex = position + (rotation * Vector3f(0, height, 0));

		for (std::size_t i = 0; i <= sides; ++i)
		{
			float r = Math::TwoPi * (i / (float)sides);
			Vector3f vertex(radius * cos(r), 0.0f, radius * sin(r));
			vertices.push_back(position + (rotation * vertex));
		}

		for (std::size_t i = 0; i < sides; ++i)
		{
			DrawLine(vertices[i], vertices[i + 1], colour);
			DrawLine(vertices[i], topVertex, colour);
		}
	}

	void LineRenderer::BufferVertex(const Vector3f& position, const Vector4f& colour)
	{
		if (_vertexCount >= _maxVertexCount)
		{
			return;
		}

		uint8_t* vertexData = &_buffer[_vertexCount * VertexSize];
		*(Vector3f*)(vertexData) = position;
		*(Vector4f*)(vertexData + sizeof(Vector3f)) = colour;

		_vertexCount++;
	}
}
