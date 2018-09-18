#version 430 core
layout (location = 0) in vec3 position;

out vec3 TexCoord;
 
uniform mat4 model;
uniform mat4 vp;
 
void main()
{
	gl_Position = vp * model * vec4(position, 1.0);
	TexCoord = position;
}