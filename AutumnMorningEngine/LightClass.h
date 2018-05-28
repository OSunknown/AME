#pragma once

#include "Math.h"
#include "Debug.h"
class LightClass
{
public:
	LightClass();
	LightClass(const LightClass&);
	~LightClass();
	
	void SetAmbientColor(float, float, float, float);
	void SetDiffuseColor(float, float, float, float);
	void SetDirection(float, float, float);
	void SetSpecularColor(float, float, float, float);
	void SetSpecularPower(float);

	Vector4 GetAmbientColor();
	Vector4 GetDiffuseColor() ;
	Vector3 GetDirection();
	Vector4 GetSpecularColor();
	float GetSpecularPower();

private:
	Vector4 m_ambientColor;
	Vector4 m_diffuseColor;
	Vector3 m_direction;
	Vector4 m_specularColor;
	float m_specularPower;
};

