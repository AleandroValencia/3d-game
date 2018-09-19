#ifndef _CAMERA_H__
#define _CAMERA_H__
#pragma once

#include "TransformComponent.h"
#include "Utils.h"

class Camera
{
public:
	Camera();
	~Camera();

	glm::mat4 View();
	glm::mat4 Projection();

	float GetFOV() const { return m_fov; }
	float GetNearPlane() const { return m_near; }
	float GetFarPlane() const { return m_far; }

	void SetFOV(float _fov) { m_fov = _fov; }
	void SetNearPlane(float _near) { m_near = _near; }
	void SetFarPlane(float _far) { m_far = _far; }

	void MoveForward() { m_transform->position += m_transform->forward * m_speed; }
	void MoveBackward() { m_transform->position -= m_transform->forward * m_speed; }
	void MoveLeft() { m_transform->position -= glm::normalize(glm::cross(m_transform->forward, m_transform->up)) * m_speed; }
	void MoveRight() { m_transform->position += glm::normalize(glm::cross(m_transform->forward, m_transform->up)) * m_speed; }

	void Rotate(glm::vec3 _eulers);
	void RotateAround(Transform& _object, glm::vec3 _eulers);

	Transform* m_transform;
private:
	float m_speed;

	GLfloat m_pitch;
	GLfloat m_yaw;

	// Perspective camera
	float m_fov;
	float m_near;
	float m_far;

	// Orthographic camera
	GLfloat m_left;
	GLfloat m_right;
	GLfloat m_top;
	GLfloat m_bottom;
};

#endif // !_CAMERA_H__
