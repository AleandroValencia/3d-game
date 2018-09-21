#version 430 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 Color;
 
uniform mat4 vp;
 
void main(void)
{
	gl_Position = vp * vec4(position, 1.0);
	Color = color;
}