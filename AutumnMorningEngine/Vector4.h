#pragma once
#include "stdafx.h"
#include"Matrix4.h"
struct Vector4
{
public:
	float x;
	float y;
	float z;
	float w;
public:
	Vector4() : x(0), y(0), z(0), w(0) { x = 0; y = 0; z = 0; w = 0; };
//	Vector4(const Vector3 *v, float Inw) { x = (v->x); y = (v->y); z = (v->z); w = (Inw); };
	Vector4(const Vector4 *v) { x = (v->x); y = (v->y); z = (v->z); w = (v->w); };
	Vector4(float InX, float InY, float InZ, float InW); //: x(InX), y(InY), z(InZ), w(InW)
	~Vector4() {};
public://Static Properties
	static const Vector4 Vector4::zero;
	static const Vector4 Vector4::one;
public:
	Vector4& operator+(const Vector4&) const;
	Vector4& operator-(const Vector4&) const;
	Vector4& operator*(const float&) const;
	Vector4& operator*(const Matrix4&) const;
	Vector4& operator/(const float&) const;
	Vector4& operator+=(const Vector4&);
	Vector4& operator-=(const Vector4&);
	
public:
	float Dist(const Vector4 &V1, const Vector4 &V2);
	float DistSquared(const Vector4 &V1, const Vector4 &V2);
};


FORCEINLINE Vector4& Vector4::operator+(const Vector4& v) const
{
	Vector4 result;
	result.x = x + v.x;
	result.y = y + v.y;
	result.z = z + v.z;
	result.w = w + v.w;
	return result;
}

FORCEINLINE Vector4& Vector4::operator-(const Vector4& v) const
{
	Vector4 result;
	result.x = x - v.x;
	result.y = y - v.y;
	result.z = z - v.z;
	result.w = w - v.w;
	return result;
}

FORCEINLINE Vector4& Vector4::operator*(const float& scalar) const
{
	Vector4 result;
	result.x = x * scalar;
	result.y = y * scalar;
	result.z = z * scalar;
	return result;
}

FORCEINLINE Vector4 & Vector4::operator*(const Matrix4 & m) const
{
	return Vector4 (
		x * m._11 + y * m._21 + z * m._31 + w * m._41, //x
		x * m._12 + y * m._22 + z * m._32 + w * m._42, //y
		x * m._13 + y * m._23 + z * m._33 + w * m._43, //z
		x * m._14 + y * m._24 + z * m._34 + w * m._44);//w
	/*result.x = x * m._11 + y * m._21 + z * m._31 + w * m._41;
	result.y = x * m._12 + y * m._22 + z * m._32 + w * m._42;
	result.z = x * m._13 + y * m._23 + z * m._33 + w * m._43;
	result.w = x * m._14 + y * m._24 + z * m._34 + w * m._44;*/
	//return result; //경고 C4172  해결 방법을 모르겠음..
}

FORCEINLINE Vector4& Vector4::operator/(const float& scalar) const
{
	Vector4 result;
	result.x = x / scalar;
	result.y = y / scalar;
	result.z = z / scalar;
	return result;
}

FORCEINLINE Vector4& Vector4::operator+=(const Vector4& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

FORCEINLINE Vector4& Vector4::operator-=(const Vector4& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

//float Vector3::Dist(const Vector3 &V1, const Vector3 &V2)
//{
//	return sqrtf(Vector3::DistSquared(V1, V2));
//}

//float Vector3::DistSquared(const Vector3 &V1, const Vector3 &V2)
//{
//	return (V2.X - V1.X) * (V2.X - V1.X) + (V2.Y - V1.Y) * (V2.Y - V1.Y) +(V2.Z - V1.Z) * (V2.Z - V1.Z) ;
//}

