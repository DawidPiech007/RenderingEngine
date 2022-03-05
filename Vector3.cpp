#include "Vector3.h"

Vector3::Vector3() : x(0), y(0), z(0)
{
}

Vector3::Vector3(float x, float y, float z): x(x), y(y), z(z)
{
}

Vector3 Vector3::operator+(Vector3& b)
{
	return Vector3(x + b.x, y + b.y, z + b.z);
}
