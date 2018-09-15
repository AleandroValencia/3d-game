#ifndef _GRAPHICSCOMPONENT_H__
#define _GRAPHICSCOMPONENT_H__
#pragma once

#include "Dependencies\glew\glew.h"

#include "Utils.h"

class GameObject;

class GraphicsComponent
{
public:
	virtual ~GraphicsComponent() {};
	virtual void Update(GameObject& _gameObject) = 0;
	virtual void Initialise() = 0;

	void SetProgram(GLuint _program) { m_program = _program; }
	void SetTexture(GLuint _texture);

protected:
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