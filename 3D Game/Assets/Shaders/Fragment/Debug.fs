#version 430 core

out vec4 color;

in vec3 Color;

void main()
{
	color = vec4(Color, 1.0f);
}