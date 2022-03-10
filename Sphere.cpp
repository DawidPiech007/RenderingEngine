#include "Sphere.hpp"
#include "Vector3.hpp"

Sphere::Sphere(Vector3& c, float r): r(r)
{
	this->c = new Vector3(c.x, c.y, c.z);
}

Sphere::Sphere()
{
	this->c = new Vector3();
	r = 0;
}

Vector3* Sphere::Intersect(Ray& ray)
{
	return nullptr;
}
