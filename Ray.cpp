#include "Ray.h"

Ray::Ray() : origin(Vector3()) {}

Ray::Ray(Vector3 origin, Vector3 direction) 
{
	this->origin = origin;
	this->direction = direction.Normalize();
}

Vector3 Ray::RayStep(float t)
{
	Vector3 value = direction * t;
	return origin + value;
}
