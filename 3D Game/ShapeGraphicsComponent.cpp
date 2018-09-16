#include "ShapeGraphicsComponent.h"

void ShapeGraphicsComponent::Initialise()
{
	m_color = glm::vec3(1.0f, 1.0f, 1.0f);

	//m_shape = kCube;

	switch (m_shape)
	{
	case kTriangle: Utils::setTriData(m_vertices, m_indices); break;
	case kQuad: Utils::setQuadData(m_vertices, m_indices); break;
	case kCube: Utils::setCubeData(m_vertices, m_indices); break;
	case kSphere: Utils::setSphereData(m_vertices, m_indices); break;
	default: Utils::setCubeData(m_vertices, m_indices);	break;
	}

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_indices.size(), &m_indices[0], GL_STATIC_DRAW);

	//this->setTexture(texFileName);

	//Attributes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::texCoord)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::normal)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void ShapeGraphicsComponent::Update(GameObject& _gameObject)
{
	glUseProgram(m_program);

	// Texture
	if (textureSet)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glUniform1i(glGetUniformLocation(m_program, "Texture"), 0);
	}

	glm::mat4 model;
	model = glm::translate(model, _gameObject.m_transform->position);
	model = glm::rotate(model, glm::radians(_gameObject.m_transform->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(_gameObject.m_transform->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(_gameObject.m_transform->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, _gameObject.m_transform->scale);

	glm::mat4 view = _gameObject.m_camera->View();
	glm::mat4 projection = _gameObject.m_camera->Projection();
	glm::mat4 vp = projection * view;

	GLint vpLoc = glGetUniformLocation(m_program, "vp");
	glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));

	GLint modelLoc = glGetUniformLocation(m_program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	GLint objColorLoc = glGetUniformLocation(m_program, "objectColor");
	glUniform3f(objColorLoc, m_color.x, m_color.y, m_color.z);

	GLuint cameraPosLoc = glGetUniformLocation(m_program, "cameraPos");
	glUniform3f(cameraPosLoc, _gameObject.m_camera->m_transform->position.x, _gameObject.m_camera->m_transform->position.y, _gameObject.m_camera->m_transform->position.z);

	//GLuint lightPosLoc = glGetUniformLocation(m_program, "lightPos");
	//glUniform3f(lightPosLoc, this->light->getPosition().x, this->light->getPosition().y, this->light->getPosition().z);

	//GLuint lightColorLoc = glGetUniformLocation(m_program, "lightColor");
	//glUniform3f(lightColorLoc, this->light->getColor().x, this->light->getColor().y, this->light->getColor().z);

	//GLuint specularStrengthLoc = glGetUniformLocation(m_program, "specularStrength");
	//glUniform1f(specularStrengthLoc, specularStrength);

	//GLuint ambientStrengthLoc = glGetUniformLocation(m_program, "ambientStrength");
	//glUniform1f(ambientStrengthLoc, ambientStrength);

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
