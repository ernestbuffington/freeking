#ifdef VERTEX

layout(location = 0) in vec2 vert_position;
layout(location = 1) in vec2 vert_texcoord;
layout(location = 2) in vec4 vert_color;

uniform GlobalUniforms
{
    mat4 viewMatrix;
    mat4 projectionMatrix;
    mat4 viewProjectionMatrix;
};

out VertexData
{
	vec2 texcoord;
	vec4 color;
} vert;

void main()
{
	vert.texcoord = vert_texcoord;
	vert.color = vert_color;
	gl_Position = projectionMatrix * vec4(vert_position.xy, 1.0, 1.0);
}

#endif

#ifdef FRAGMENT

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

#endif
