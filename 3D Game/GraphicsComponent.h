#ifndef _GRAPHICSCOMPONENT_H__
#define _GRAPHICSCOMPONENT_H__
#pragma once

#include "Dependencies\glew\glew.h"
#include "Dependencies\sdl_image\include\SDL_image.h"

#include "Utils.h"

class GameObject;

class GraphicsComponent
{
public:
	virtual ~GraphicsComponent() {};
	virtual void Update() = 0;
	virtual void Initialise(GameObject* _gameObject) = 0;

	void SetProgram(GLuint _program) { m_program = _program; }
	void SetTexture(std::string _filePath);
	void SetTextures(std::vector<std::string>& _textures);

protected:
	GameObject* m_gameObject;

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;
	GLuint m_texture;
	GLuint m_program;

	bool textureSet = false;

	std::vector<VertexFormat> m_vertices;
	std::vector<GLuint> m_indices;

	glm::vec3 m_color;
	float m_specular;
	float m_ambient;
};
#endif // !_GRAPHICSCOMPONENT_H__