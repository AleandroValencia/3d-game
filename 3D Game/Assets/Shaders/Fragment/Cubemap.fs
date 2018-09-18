#version 430 core

in vec3 TexCoord;
out vec4 color;

uniform samplerCube skyBox;

void main()
{
	color = texture(skyBox, TexCoord);
	//color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}