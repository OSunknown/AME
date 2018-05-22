#pragma once
#include "stdafx.h"

struct Matrix2
{
public:
	float _11, _12;
	float _21, _22;
public:
	Matrix2() : _11(0), _12(0), _21(0), _22(0) {};
	Matrix2(float In11, float In12, float In21, float In22) : _11(In11), _12(In12), _21(In21), _22(In22) {};
	~Matrix2() {};
public:
	Matrix2 operator+(const Matrix2& other) const;
	Matrix2 operator-(const Matrix2& other) const;
	Matrix2 operator*(const Matrix2& other) const;
	Matrix2 operator*(const float& scale) const;

	Matrix2 operator+=(const Matrix2& other);
	Matrix2 operator-=(const Matrix2& other);
	Matrix2 operator*=(const Matrix2& other);
	Matrix2 operator*=(const float& scale);
	bool operator ==(const Matrix2& other);

public:
	void SetIdentity()
	{
		_11 = 1.0f;
		_12 = 0.0f;
		_21 = 0.0f;
		_22 = 1.0f;
	}
	void SetScale(float a, float b)
	{
		SetIdentity();
		_11 = a;
		_22 = b;
	}
	
	void SetRotation(float degree)
	{
		float radian = Deg2Rad(degree);
		_11 = cosf(radian);
		_12 = -sinf(radian);
		_21 = sinf(radian);
		_22 = cosf(radian);
	}
};

FORCEINLINE Matrix2 Matrix2::operator+(const Matrix2& other) const
{
	Matrix2 result;
	result._11 = _11 + other._11;
	result._12 = _12 + other._12;
	result._21 = _21 + other._21;
	result._22 = _22 + other._22;
	return result;
}

FORCEINLINE Matrix2 Matrix2::operator-(const Matrix2& other) const
{
	Matrix2 result;
	result._11 = _11 - other._11;
	result._12 = _12 - other._12;
	result._21 = _21 - other._21;
	result._22 = _22 - other._22;
	return result;
}


FORCEINLINE Matrix2 Matrix2::operator*(const Matrix2& other) const
{
	Matrix2 result;
	result._11 = _11 * other._11 + _12 * other._21;
	result._12 = _11 * other._12 + _12 * other._22;
	result._21 = _21 * other._11 + _22 * other._21;
	result._22 = _21 * other._12 + _22 * other._22;
	return result;
}

FORCEINLINE Matrix2 Matrix2::operator*(const float& scale) const
{
	Matrix2 result;
	result._11 = _11 * scale;
	result._12 = _12 * scale;
	result._21 = _21 * scale;
	result._22 = _22 * scale;
	return result;
}

FORCEINLINE Matrix2 Matrix2::operator+=(const Matrix2& other) 
{
	_11 = _11 + other._11;
	_12 = _12 + other._12;
	_21 = _21 + other._21;
	_22 = _22 + other._22;
	return *this;
}

FORCEINLINE Matrix2 Matrix2::operator-=(const Matrix2& other) 
{
	_11 = _11 - other._11;
	_12 = _12 - other._12;
	_21 = _21 - other._21;
	_22 = _22 - other._22;
	return *this;
}

FORCEINLINE Matrix2 Matrix2::operator*=(const Matrix2& other) 
{
	_11 = _11 * other._11 + _12 * other._21;
	_12 = _11 * other._12 + _12 * other._22;
	_21 = _21 * other._11 + _22 * other._21;
	_22 = _21 * other._12 + _22 * other._22;
	return *this;
}

FORCEINLINE Matrix2 Matrix2::operator*=(const float& scale) 
{
	_11 = _11 * scale;
	_12 = _12 * scale;
	_21 = _21 * scale;
	_22 = _22 * scale;
	return *this;
}

FORCEINLINE bool Matrix2::operator==(const Matrix2 & other)
{
	if (_11 == other._11 && _12 == other._12 &&
		_21 == other._21 && _22 == other._22)
	{
		return true;
	}
	return false;
}
