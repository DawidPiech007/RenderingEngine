#include "Ray.hpp"

Ray::Ray() : origin(Vector3()) {}

Ray::Ray(Vector3 origin, Vector3 direction) 
{
	this->origin = origin;
	this->direction = direction;
}

Vector3 Ray::RayStep(float t)
{
	Vector3 value = direction * t;
	return origin + value;
}
