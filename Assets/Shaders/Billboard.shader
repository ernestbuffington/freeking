#ifdef VERTEX

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 offset;
layout(location = 2) in vec2 size;
layout(location = 3) in vec4 color;

out VertexData
{
	vec2 uv;
	vec4 color;
} vert;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main()
{
	vert.uv = position + vec2(0.5, 0.5);
	vert.color = color;

	vec4 p = viewMatrix * vec4(offset, 1.0);
	p.xy += position.xy * size.xy;

	gl_Position = projectionMatrix * p;
}

#endif

#ifdef FRAGMENT

in VertexData
{
	vec2 uv;
	vec4 color;
} vert;

uniform sampler2D diffuse;

out vec4 fragColor;

void main()
{
	vec4 diffuseColor = texture(diffuse, vert.uv);
	fragColor = vec4((diffuseColor.rgb * vert.color.rgb) * (diffuseColor.a * vert.color.a), 1.0);
}

#endif
