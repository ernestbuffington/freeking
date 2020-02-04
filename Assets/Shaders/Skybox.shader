#ifdef VERTEX

layout(location = 0) in vec3 position;

out VertexData
{
	vec3 uv;
} vert;

uniform mat4 viewProj;

void main()
{
	vert.uv = position;
	gl_Position = viewProj * vec4(position, 1.0);
}

#endif

#ifdef FRAGMENT

in VertexData
{
	vec3 uv;
} vert;

uniform samplerCube cubemap;

out vec4 fragColor;

void main()
{
    fragColor = texture(cubemap, vert.uv);
}

#endif
