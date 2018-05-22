#pragma once

#include "Math.h"
#include "Debug.h"
class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass &);
	~CameraClass();
	
	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	Vector3 GetPosition();
	Vector3 GetRotation();

	void Render();
	void GetViewMatrix(Matrix4&);

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	Matrix4 m_viewMatrix;
};

