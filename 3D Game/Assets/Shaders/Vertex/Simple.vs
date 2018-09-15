#version 430 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec3 outColor;
out vec2 TexCoord;
 
uniform mat4 model;
uniform mat4 vp;
 
void main(void)
{
	gl_Position = vp * model * vec4(position, 1.0);
	outColor = normal;
	TexCoord = texCoord;
}