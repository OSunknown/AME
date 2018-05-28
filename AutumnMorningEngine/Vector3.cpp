#include"Vector3.h"

Vector3::Vector3()
{
	x = 0; y = 0; z = 0;
}

Vector3::Vector3(const Vector3 * v)
{
	x = v->x;
	y = v->y;
	z = v->z;
}

Vector3::~Vector3()
{
}
