#pragma once
#include "Matrix2.h"

struct Matrix3
{
public:
	float _11, _12, _13;
	float _21, _22, _23;
	float _31, _32, _33;
public:
	Matrix3();
	~Matrix3();
public:
	Matrix3 operator+(const Matrix3& other) const;
	Matrix3 operator-(const Matrix3& other) const;
	Matrix3 operator*(const Matrix3& other) const;
	Matrix3 operator*(const float& scale) const;

	Matrix3 operator+=(const Matrix3& other);
	Matrix3 operator-=(const Matrix3& other);
	Matrix3 operator*=(const Matrix3& other);
	Matrix3 operator*=(const float& scale);
	bool operator ==(const Matrix3& other);
public:
	void SetIdentity()
	{
		_11 = 1.0f;
		_12 = 0.0f;
		_13 = 0.0f;
		_21 = 0.0f;
		_22 = 1.0f;
		_23 = 0.0f;
		_31 = 0.0f;
		_32 = 0.0f;
		_33 = 1.0f;
	}

	void SetTranslation(float InX, float InY)
	{
		SetIdentity();
		_13 = InX;
		_23 = InY;
	}

	void SetRotation(float degree)
	{
		SetIdentity();
		_11 = cosf(Deg2Rad(degree));
		_12 = -sinf(Deg2Rad(degree));
		_21 = -_12;
		_22 = _11;
	}

	void SetScale(float a, float b)
	{
		SetIdentity();
		_11 = a;
		_22 = b;
	}

	Matrix3 TRS(float TransX, float TransY, float degree, float scale) { return TRS(TransX, TransY, degree, scale, scale); };
//	Matrix3 TRS(float TransX, float TransY, float degree, Vector2 scale) { return TRS(TransX, TransY, degree, scale.x, scale.y);};
	Matrix3 TRS(float TransX, float TransY, float degree, float scaleX, float scaleY)
	{
		Matrix3 TMat, RMat, SMat;
		TMat.SetTranslation(TransX, TransY);
		RMat.SetRotation(degree);
		SMat.SetScale(scaleX, scaleY);
		*this = TMat * RMat * SMat;
		return *this;
	}
};


FORCEINLINE Matrix3 Matrix3::operator+(const Matrix3& other) const
{
	Matrix3 result;
	result._11 = _11 + other._11;
	result._12 = _12 + other._12;
	result._21 = _21 + other._21;
	result._22 = _22 + other._22;
	return result;
}

FORCEINLINE Matrix3 Matrix3::operator-(const Matrix3& other) const
{
	Matrix3 result;
	result._11 = _11 - other._11;
	result._12 = _12 - other._12;
	result._21 = _21 - other._21;
	result._22 = _22 - other._22;
	return result;
}


FORCEINLINE Matrix3 Matrix3::operator*(const Matrix3& other) const
{
	Matrix3 result;
	result._11 = _11 * other._11 + _12 * other._21 + _13 * other._31;
	result._12 = _11 * other._12 + _12 * other._22 + _13 * other._32;
	result._13 = _11 * other._13 + _12 * other._23 + _13 * other._33;
	result._21 = _21 * other._11 + _22 * other._21 + _23 * other._31;
	result._22 = _21 * other._12 + _22 * other._22 + _23 * other._32;
	result._22 = _21 * other._13 + _22 * other._23 + _23 * other._33;
	result._31 = _31 * other._11 + _32 * other._21 + _33 * other._31;
	result._32 = _31 * other._12 + _32 * other._22 + _33 * other._32;
	result._32 = _31 * other._13 + _32 * other._23 + _33 * other._33;
	return result;
}

FORCEINLINE Matrix3 Matrix3::operator*(const float& scale) const
{
	Matrix3 result;
	result._11 = _11 * scale;
	result._12 = _12 * scale;
	result._21 = _21 * scale;
	result._22 = _22 * scale;
	return result;
}

FORCEINLINE Matrix3 Matrix3::operator+=(const Matrix3& other)
{
	_11 = _11 + other._11;
	_12 = _12 + other._12;
	_21 = _21 + other._21;
	_22 = _22 + other._22;
	return *this;
}

FORCEINLINE Matrix3 Matrix3::operator-=(const Matrix3& other)
{
	_11 = _11 - other._11;
	_12 = _12 - other._12;
	_21 = _21 - other._21;
	_22 = _22 - other._22;
	return *this;
}

FORCEINLINE Matrix3 Matrix3::operator*=(const Matrix3& other)
{
	_11 = _11 * other._11 + _12 * other._21;
	_12 = _11 * other._12 + _12 * other._22;
	_21 = _21 * other._11 + _22 * other._21;
	_22 = _21 * other._12 + _22 * other._22;
	return *this;
}

FORCEINLINE Matrix3 Matrix3::operator*=(const float& scale)
{
	_11 = _11 * scale;
	_12 = _12 * scale;
	_21 = _21 * scale;
	_22 = _22 * scale;
	return *this;
}

FORCEINLINE bool Matrix3::operator==(const Matrix3 & other)
{
	if (_11 == other._11 && _12 == other._12 &&
		_21 == other._21 && _22 == other._22)
	{
		return true;
	}
	return false;
}