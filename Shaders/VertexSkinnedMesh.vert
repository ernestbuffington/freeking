#version 460

layout(location = 0) in vec2 uv;
layout(location = 1) in int vertexIndex;

out VertexData
{
	vec3 normal;
	vec2 uv;
} vert;

uniform mat4 viewProj;
uniform isamplerBuffer frameVertexBuffer;
uniform samplerBuffer normalBuffer;
uniform float delta;

struct Frame
{
	int index;
	vec3 translate;
	vec3 scale;
};

uniform Frame frames[2];

struct Vertex
{
	vec3 position;
	vec3 normal;
};

Vertex GetVertex(Frame frame)
{
	ivec4 frameVertex = texelFetch(frameVertexBuffer, frame.index + vertexIndex);
	vec3 position = ((frameVertex.rgb + vec3(128)) * frame.scale) + frame.translate;
	vec3 normal = texelFetch(normalBuffer, frameVertex.a + 128).rgb;

	Vertex vertex;
	vertex.position = vec3(position.x, position.z, -position.y);
	vertex.normal = vec3(normal.x, normal.z, -normal.y);
	return vertex;
}

vec3 Lerp(vec3 a, vec3 b, float t)
{
	return (t >= 0.0f) ? mix(a, b, t) : a;
}

void main()
{
	Vertex vertex = GetVertex(frames[0]);
	Vertex nextVertex = GetVertex(frames[1]);

	vec3 lerpPosition = Lerp(vertex.position, nextVertex.position, delta);
	vec3 lerpNormal = Lerp(vertex.normal, nextVertex.normal, delta);

	vert.uv = uv;
	vert.normal = lerpNormal;

	gl_Position = viewProj * vec4(lerpPosition, 1.0);
}
