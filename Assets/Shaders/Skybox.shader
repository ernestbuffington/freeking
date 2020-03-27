#ifdef VERTEX

layout(location = 0) in vec3 position;

uniform GlobalUniforms
{
    mat4 viewMatrix;
    mat4 projectionMatrix;
    mat4 viewProjectionMatrix;
};

out VertexData
{
	vec3 uv;
} vert;

void main()
{
	vert.uv = position;
	gl_Position = (projectionMatrix * viewMatrix * vec4(position, 1.0)).xyww;
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
