#include "Plane.h"
#include "Vector3.h"
#include "Ray.h"
#include <iostream>

Plane::Plane(Vector3 point, Vector3 normal) : point(point), normal(normal) {}

Plane::Plane(Vector3 point, Vector3 normal, Material* material)
{
	this->point = point;
	this->normal = normal;
	this->material = material;
}

Intersection* Plane::GetIntersection(Ray& ray, bool backsidedClipping)
{
	// TODO: zaimplementowaæ backsidedClipping

	float plane = Vector3::Dot(point, normal);
	float dot1 = plane - Vector3::Dot(ray.origin, normal);
	float dot2 = Vector3::Dot(normal, ray.direction);

	if (dot2 != 0)
	{
		float t = dot1 / dot2;
		if (t > 0)
		{
			return new Intersection(Vector3(ray.RayStep(t)),normal);
		}
	}

	return nullptr;
}
