#version 460

uniform sampler2D texture;

in VertexData
{
	vec2 texcoord;
	vec4 color;
} vert;

out vec4 fragColor;

float median(float r, float g, float b)
{
	return max(min(r, g), min(max(r, g), b));
}

void main()
{
	vec3 color = 1.0 - texture2D(texture, vert.texcoord).rgb;
	float sigDist = median(color.r, color.g, color.b) - 0.5;
	float alpha = clamp(sigDist / fwidth(sigDist) + 0.5, 0.0, 1.0);
	fragColor = vec4(vert.color.rgb, alpha * vert.color.a);
	if (fragColor.a < 0.0001) discard;	
}
