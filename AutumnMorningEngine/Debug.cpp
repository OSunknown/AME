#include"Debug.h"

void Debug::Log(const char * value)
{
	printf(value);
	return;
}

void Debug::Log(const float value)
{
	printf("%f \n",value);
	return;
}

void Debug::Log(const int value)
{
	printf("%d \n", value);
	return;
}

void Debug::Log(Vector2 value)
{
	printf("(%.3f, %.3f)\n", value.x, value.y);
	return;
}

void Debug::Log(Vector3 value)
{
	printf("(%f, %f, %f)\n", value.x, value.y, value.z);
	return;
}

void Debug::Log(const Vector4& value)
{
	printf("(%f, %f, %f, %f)\n", value.x, value.y, value.z, value.w);
	return;
}

void Debug::Log(const Matrix4 & value)
{
	printf("=========================\n");
	printf("(%f, %f, %f, %f)\n", value._11, value._12, value._13, value._14);
	printf("(%f, %f, %f, %f)\n", value._21, value._22, value._23, value._24);
	printf("(%f, %f, %f, %f)\n", value._31, value._32, value._33, value._34);
	printf("(%f, %f, %f, %f)\n", value._41, value._42, value._43, value._44);
	printf("=========================\n");
	return;
}

void Debug::Log(D3DXVECTOR3 value)
{
	printf("(%.3f, %.3f, %.3f)\n", value.x, value.y, value.z);
}

void Debug::Log(D3DXVECTOR4 value)
{
	printf("(%.3f, %.3f, %.3f, %.3f)\n", value.x, value.y, value.z, value.w);
}