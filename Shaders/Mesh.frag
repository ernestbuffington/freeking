#version 460

uniform sampler2D diffuse;
uniform sampler2D lightmap;
uniform float brightness;

in VertexData
{
	vec3 normal;
	vec2 uv0;
	vec2 uv1;
	vec2 uv2;
} vert;

out vec4 fragColor;

void main()
{
	vec3 textureColor = texture(diffuse, vert.uv0).rgb;
	vec3 lightmapColor0 = texture(lightmap, vert.uv1).rgb * 2.0;
	vec3 lightmapColor1 = texture(lightmap, vert.uv2).rgb * brightness;
	vec3 lightmapColor = lightmapColor0 + lightmapColor1;

	float gamma = 1.5;
	textureColor.rgb = pow(textureColor.rgb, vec3(1.0 / gamma));

    fragColor = vec4(textureColor.rgb * lightmapColor.rgb, 1.0);
}
