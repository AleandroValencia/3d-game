#include "Camera.h"

Camera::Camera()
	: m_fov(45.0f)
	, m_near(0.1f)
	, m_far(1000.0f)
	, m_speed(0.1f)
	, m_pitch(0.0f)
	, m_yaw(-90.0f)
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

void Camera::Rotate(glm::vec3 _eulers)
{
	m_yaw += _eulers.x;
	m_pitch += _eulers.y;

	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	m_transform->forward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_transform->forward.y = sin(glm::radians(m_pitch));
	m_transform->forward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
}
