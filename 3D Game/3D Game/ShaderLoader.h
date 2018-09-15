#ifndef _SHADERLOADER_H__
#define _SHADERLOADER_H__
#pragma once

#include "glew.h"
#include "ShaderLoader.h"
#include <iostream>
#include<fstream>
#include<vector>

class ShaderLoader
{
public:

	ShaderLoader(void);
	~ShaderLoader(void);
	GLuint CreateProgram(char* VertexShaderFilename, char* FragmentShaderFilename);
	GLuint CreateProgram(char* VertexShaderFilename, char* FragmentShaderFilename, char* GeometryShaderFilename);
	GLuint CreateProgram(char* VertexShaderFilename, char* FragmentShaderFilename, char* TessControlShaderFilename, char* TessEvalShaderFilename);
	GLuint CreateCompProgram(char* ComputeShaderFilename);

private:
	std::string ReadShader(char *filename);
	GLuint CreateShader(GLenum shaderType, std::string source, char* shaderName);
};

#endif // !_SHADERLOADER_H__
