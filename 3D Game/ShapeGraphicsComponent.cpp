#include "ShapeGraphicsComponent.h"

void ShapeGraphicsComponent::Initialise(GameObject* _gameObject)
{
	m_gameObject = _gameObject;
	m_color = glm::vec3(1.0f, 1.0f, 1.0f);

	switch (m_shape)
	{
	case TRIANGLE: Utils::setTriData(m_vertices, m_indices); break;
	case QUAD: Utils::setQuadData(m_vertices, m_indices); break;
	case CUBE: Utils::setCubeData(m_vertices, m_indices); break;
	case SPHERE: Utils::setSphereData(m_vertices, m_indices); break;
	case SKYBOXSHAPE: Utils::setSkyBoxData(m_vertices, m_indices); break;
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

void ShapeGraphicsComponent::Update()
{
	glUseProgram(m_program);

	// Texture
	if (textureSet)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glUniform1i(glGetUniformLocation(m_program, "Texture"), 0);
	}

	glm::mat4 model = glm::mat4();
	model = glm::translate(model, m_gameObject->GetPosition());
	model = glm::rotate(model, glm::radians(m_gameObject->GetRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(m_gameObject->GetRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(m_gameObject->GetRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, m_gameObject->GetScale());

	glm::mat4 view = m_gameObject->m_camera->View();
	glm::mat4 projection = m_gameObject->m_camera->Projection();
	glm::mat4 vp = projection * view;

	GLint vpLoc = glGetUniformLocation(m_program, "vp");
	glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));

	GLint modelLoc = glGetUniformLocation(m_program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	GLint objColorLoc = glGetUniformLocation(m_program, "objectColor");
	glUniform3f(objColorLoc, m_color.x, m_color.y, m_color.z);

	if (m_gameObject->GetLight())
	{
		GLuint viewPosLoc = glGetUniformLocation(m_program, "viewPos");
		glUniform3f(viewPosLoc, m_gameObject->m_camera->m_transform->position.x, m_gameObject->m_camera->m_transform->position.y, m_gameObject->m_camera->m_transform->position.z);

		GLuint lightPosLoc = glGetUniformLocation(m_program, "lightPos");
		glUniform3f(lightPosLoc, m_gameObject->GetLight()->GetPosition().x, m_gameObject->GetLight()->GetPosition().y, m_gameObject->GetLight()->GetPosition().z);

		GLuint lightColorLoc = glGetUniformLocation(m_program, "lightColor");
		glUniform3f(lightColorLoc, m_gameObject->GetLight()->GetColor().x, m_gameObject->GetLight()->GetColor().y, m_gameObject->GetLight()->GetColor().z);

		GLuint specularStrengthLoc = glGetUniformLocation(m_program, "specularStrength");
		glUniform1f(specularStrengthLoc, m_gameObject->GetLight()->GetSpecular());

		GLuint ambientStrengthLoc = glGetUniformLocation(m_program, "ambientStrength");
		glUniform1f(ambientStrengthLoc, m_gameObject->GetLight()->GetAmbient());
	}

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
