#include "Ray.hpp"

Ray::Ray() : origin(Vector3()) {}

Ray::Ray(Vector3 origin, Vector3 direction) 
{
	this->origin = origin;
	this->direction = direction;
}
