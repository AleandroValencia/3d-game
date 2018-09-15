#include "Camera.h"

Camera::Camera()
	: m_fov(45.0f)
	, m_near(0.1f)
	, m_far(1000.0f)
{
	m_transform = new Transform();
}

Camera::~Camera()
{
	delete m_transform;
	m_transform = nullptr;
}

glm::mat4 Camera::View()
{
	return glm::lookAt(m_transform->position, m_transform->position + m_transform->forward, m_transform->up);
}

glm::mat4 Camera::Projection()
{
	return glm::perspective(m_fov, static_cast<GLfloat>(Utils::WIDTH) / static_cast<GLfloat>(Utils::HEIGHT), m_near, m_far);
}
