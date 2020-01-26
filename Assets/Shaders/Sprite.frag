#version 460

uniform sampler2D texture;

in VertexData
{
	vec2 texcoord;
	vec4 color;
} vert;

out vec4 fragColor;

void main()
{
	vec4 textureColor = texture2D(texture, vert.texcoord);
	fragColor = textureColor * vert.color;
}
