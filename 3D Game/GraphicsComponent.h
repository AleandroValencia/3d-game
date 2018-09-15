#ifndef _GRAPHICSCOMPONENT_H__
#define _GRAPHICSCOMPONENT_H__
#pragma once

#include "Dependencies\glew\glew.h"

#include "Utils.h"
#include "GameObject.h"

class GraphicsComponent
{
public:
	virtual ~GraphicsComponent() {};
	virtual void Update(GameObject& _gameObject) = 0;

	void Initialise();
	void SetProgram(GLuint _program) { m_program = _program; }
	void SetTexture(GLuint _texture);

private:
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

	ModelType m_shape;
};
#endif // !_GRAPHICSCOMPONENT_H__