#version 430 core

out vec4 color;

in vec3 outColor;
in vec2 TexCoord;

uniform sampler2D Texture;

void main()
{
	color = vec4(outColor, 1.0f);
}