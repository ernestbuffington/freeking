#version 460

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv0;
layout(location = 3) in vec2 uv1;
layout(location = 4) in vec2 uv2;

out VertexData
{
	vec3 normal;
	vec2 uv0;
	vec2 uv1;
	vec2 uv2;
} vert;

uniform mat4 viewProj;

void main()
{
	vert.normal = normal;
	vert.uv0 = uv0;
	vert.uv1 = uv1;
	vert.uv2 = uv2;

	gl_Position = viewProj * vec4(position, 1.0);
}
