#version 460

uniform sampler2D diffuse;

in VertexData
{
	vec3 normal;
	vec2 uv;
} vert;

out vec4 fragColor;

void main()
{
	vec3 textureColor = texture(diffuse, vert.uv).rgb;
	vec3 normal = normalize(vert.normal);
	
    fragColor = vec4(textureColor.rgb, 1.0);
}
