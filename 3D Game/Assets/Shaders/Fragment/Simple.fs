#version 430 core

out vec4 color;

in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D Texture;
uniform vec3 objectColor;

void main()
{
	color = vec4(objectColor, 1.0f);
}