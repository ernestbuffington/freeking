#include "LineRenderer.h"
#include "Shader.h"

namespace Freeking
{
	std::shared_ptr<LineRenderer> LineRenderer::Debug = nullptr;

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

		_shader = Shader::Library.Get("Shaders/DebugLine.shader");
	}

	void LineRenderer::Flush(Matrix4x4& viewProj)
	{
		if (_vertexCount < 2)
		{
			return;
		}

		_vertexBuffer->UpdateBuffer(_buffer.data(), 0, _vertexCount * VertexSize);

		_shader->Apply();

		_vertexBinding->Bind();
		glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(_vertexCount));
		_vertexBinding->Unbind();

		_vertexCount = 0;

		_shader->Unbind();
	}

	void LineRenderer::Clear()
	{
		_vertexCount = 0;
	}

	void LineRenderer::DrawLine(const Vector3f& p1, const Vector3f& p2, const LinearColor& colour)
	{
		BufferVertex(p1, colour);
		BufferVertex(p2, colour);
	}

	void LineRenderer::DrawBox(const Matrix4x4& transform, const Vector3f& mins, const Vector3f& maxs, const LinearColor& colour)
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

	void LineRenderer::DrawAABBox(const Vector3f& position, const Vector3f& mins, const Vector3f& maxs, const LinearColor& colour)
	{
		DrawAABBox(position + mins, position + maxs, colour);
	}

	void LineRenderer::DrawAABBox(const Vector3f& mins, const Vector3f& maxs, const LinearColor& colour)
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

	void LineRenderer::DrawSphere(const Vector3f& position, float radius, int thetaSegments, int phiSegments, const LinearColor& colour)
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

	void LineRenderer::DrawAxis(const Matrix4x4& transform, float length, float size)
	{
		Vector3f start = transform.Translation();
		Vector3f p1 = transform.Transform(Vector3f::OneX);
		Vector3f p2 = transform.Transform(Vector3f::OneY);
		Vector3f p3 = transform.Transform(Vector3f::OneZ);

		DrawArrow(start, start + p1 * length, p2, p3, size, LinearColor::Red);
		DrawArrow(start, start + p2 * length, p3, p1, size, LinearColor::Green);
		DrawArrow(start, start + p3 * length, p1, p2, size, LinearColor::Blue);
	}

	void LineRenderer::DrawArrow(const Vector3f& start, const Vector3f& end, const Vector3f& up, const Vector3f& right, const float size, const LinearColor& color)
	{
		static const float degreeStep = 30.0f;

		static const float arrowSin[45] = {
			0.0f, 0.5f, 0.866025f, 1.0f, 0.866025f, 0.5f, -0.0f, -0.5f, -0.866025f,
			-1.0f, -0.866025f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
		};

		static const float arrowCos[45] = {
			1.0f, 0.866025f, 0.5f, -0.0f, -0.5f, -0.866026f, -1.0f, -0.866025f, -0.5f, 0.0f,
			0.5f, 0.866026f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
		};

		DrawLine(start, end, color);

		Vector3f forward = (end - start).Normalise() * size;
		float degrees = 0.0f;

		for (int i = 0; degrees < 360.0f; degrees += degreeStep, ++i)
		{
			Vector3f v1(end - forward + up * ((size * arrowCos[i]) * 0.5f) + right * ((size * arrowSin[i]) * 0.5f));
			Vector3f v2(end - forward + up * ((size * arrowCos[i + 1]) * 0.5f) + right * ((size * arrowSin[i + 1]) * 0.5f));

			DrawLine(v1, end, color);
			DrawLine(v1, v2, color);
		}
	}

	void LineRenderer::BufferVertex(const Vector3f& position, const LinearColor& colour)
	{
		if (_vertexCount >= _maxVertexCount)
		{
			return;
		}

		uint8_t* vertexData = &_buffer[_vertexCount * VertexSize];
		*(Vector3f*)(vertexData) = position;
		*(LinearColor*)(vertexData + sizeof(Vector3f)) = colour;

		_vertexCount++;
	}
}
