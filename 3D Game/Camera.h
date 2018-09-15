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

	Transform* m_transform;
private:
	
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
