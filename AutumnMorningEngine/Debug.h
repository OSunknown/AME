#pragma once
#include "Math.h"
#include <D3DX10math.h>
struct Debug
{
public:
	static void Log(const char *  );
	static void Log(const float value);
	static void Log(const int value);
	static void Log(Vector2);
	static void Log(Vector3);
	static void Log(const Vector4& );
	static void Log(const Matrix4&);
	static void Log(D3DXVECTOR3);
	static void Log(D3DXVECTOR4);
};


