#pragma once
#include "stdafx.h"
#include "Matrix2.h"
struct Vector2
{
public:
	float x;
	float y;
public://Static Praoperties
	static const Vector2 Vector2::zero;
	static const Vector2 Vector2::one;
public:
	Vector2() : x(0), y(0) {};
	Vector2(float InX, float InY) : x(InX), y(InY) {};
	~Vector2() {};
public:
	Vector2 operator+(const Vector2&) const;
	Vector2 operator-(const Vector2&) const;
	Vector2 operator*(const float&) const;
	Vector2 operator*(const Matrix2&) const;
	Vector2 operator/(const float&) const;
	Vector2 operator+=(const Vector2&);
	Vector2 operator-=(const Vector2&);
	bool operator==(const Vector2&) const;
public:
	float Dist(const Vector2 &V1, const Vector2 &V2)
	{
		return sqrtf(Vector2::DistSquared(V1, V2));
	}
	float DistSquared(const Vector2 &V1, const Vector2 &V2)
	{
		return (V2.x - V1.x) * (V2.x - V1.x) + (V2.y - V1.y) * (V2.y - V1.y);
	}
	bool Equle(const Vector2 & V) const
	{
		if (x == V.x && y == V.y)
		{
			return true;
		}
		return false;
	}
};

FORCEINLINE Vector2 Vector2::operator+(const Vector2& v) const
{
	Vector2 result;
	result.x = x + v.x;
	result.y = y + v.y;
	return result;
}

FORCEINLINE Vector2 Vector2::operator-(const Vector2& v) const
{
	Vector2 result;
	result.x = x - v.x;
	result.y = y - v.y;
	return result;
}

FORCEINLINE Vector2 Vector2::operator*(const float& scale) const
{
	Vector2 result;
	result.x = x * scale;
	result.y = y * scale;
	return result;
}

FORCEINLINE Vector2 Vector2::operator*(const Matrix2 & mat) const
{
	Vector2 result;
	result.x = x * mat._11 + y + mat._12;
	result.y = y * mat._21 + y + mat._22;
	return Vector2();
}

FORCEINLINE Vector2 Vector2::operator/(const float& scale) const
{
	Vector2 result;
	result.x = x / scale;
	result.y = y / scale;
	return result;
}

FORCEINLINE Vector2 Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

FORCEINLINE Vector2 Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

FORCEINLINE bool Vector2::operator==(const Vector2 & v) const
{
	if (x == v.x && y == v.y)
	{
		return true;
	}
	return false;
}
