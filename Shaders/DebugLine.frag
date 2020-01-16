#version 460

in VertexData
{
	vec4 color;
} vert;

out vec4 fragColor;

void main()
{
    fragColor = vert.color;
}
