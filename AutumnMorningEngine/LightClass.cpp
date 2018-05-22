#include "LightClass.h"


LightClass::LightClass()
{
	m_diffuseColor = Vector4::zero;
	m_direction = Vector3::zero;
}

LightClass::LightClass(const LightClass& other)
{
}

LightClass::~LightClass()
{
}

void LightClass::SetAmbientColor(float red, float green, float blue, float alpha)
{
	m_ambientColor = Vector4(red, green, blue, alpha);
}

void LightClass::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor = Vector4(red, green, blue, alpha);
	return;
}


void LightClass::SetDirection(float x, float y, float z)
{
	m_direction = Vector3(x, y, z);	
	return;
}

void LightClass::SetSpecularColor(float red, float blue, float green, float alpha)
{
	m_specularColor = Vector4(red, blue, green, alpha);
	return;
}

void LightClass::SetSpecularPower(float power)
{
	m_specularPower = power;
	return;
}


Vector4 LightClass::GetAmbientColor()
{
	return m_ambientColor;
}

Vector4 LightClass::GetDiffuseColor()
{
	return m_diffuseColor;
}


Vector3 LightClass::GetDirection()
{
	return m_direction;
}

Vector4 LightClass::GetSpecularColor()
{
	return m_specularColor;
}

float LightClass::GetSpecularPower()
{
	return m_specularPower;
}
