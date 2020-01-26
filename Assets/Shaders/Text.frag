#version 460

uniform sampler2D texture;

in VertexData
{
	vec2 texcoord;
	vec4 color;
} vert;

out vec4 fragColor;

const float smoothing = 1.0 / 4.0;

void main()
{
	float distance = texture2D(texture, vert.texcoord).a;
	float alpha = smoothstep(0.5 - smoothing, 0.5 + smoothing, distance);
	fragColor = vec4(vert.color.rgb, vert.color.a * alpha);
}
