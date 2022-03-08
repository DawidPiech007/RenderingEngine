#include "Vector3.hpp"
#include <Math.h>

Vector3::Vector3() : x(0), y(0), z(0)
{
}

Vector3::Vector3(float x, float y, float z): x(x), y(y), z(z)
{
}

Vector3 Vector3::operator+=(Vector3& b)
{
	this->x += b.x;
	this->y += b.y;
	this->z += b.z;
	return *this;
}


Vector3 Vector3::operator-=(Vector3& b)
{
	this->x -= b.x;
	this->y -= b.y;
	this->z -= b.z;
	return *this;
}

Vector3 Vector3::operator+=(Vector3 b)
{
	this->x += b.x;
	this->y += b.y;
	this->z += b.z;
	return *this;
}

Vector3 Vector3::operator-=(Vector3 b)
{
	this->x -= b.x;
	this->y -= b.y;
	this->z -= b.z;
	return *this;
}

Vector3 Vector3::operator*=(float k)
{
	this->x *= k;
	this->y *= k;
	this->z *= k;
	return *this;
}

Vector3 Vector3::operator/=(float k)
{
	this->x /= k;
	this->y /= k;
	this->z /= k;
	return *this;
}


Vector3 Vector3::operator+(Vector3& b)
{
	return Vector3(x + b.x, y + b.y, z + b.z);
}

Vector3 Vector3::operator-(Vector3& b)
{
	return Vector3(x - b.x, y - b.y, z - b.z);
}

Vector3 Vector3::operator*(float k)
{
	return Vector3(x * k, y * k, z * k);
}

Vector3 Vector3::operator/(float k)
{
	return Vector3(x / k, y / k, z / k);

}

Vector3 Vector3::operator-()
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator+()
{
	return Vector3(x, y, z);
}

Vector3 Vector3::Cross(Vector3& b)
{
	return Vector3();
}

float Vector3::Dot(Vector3& b)
{
	return this->Magnitude() * this->Magnitude();// * cos()
}

float Vector3::Magnitude(Vector3& a)
{
	return sqrtf((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
}

float Vector3::SquerMagnitude(Vector3& a)
{
	return (a.x * a.x) + (a.y * a.y) + (a.z * a.z);
}

float Vector3::Magnitude()
{
	return sqrtf((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}
