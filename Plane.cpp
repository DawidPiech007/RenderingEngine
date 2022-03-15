#include "Plane.hpp"
#include "Vector3.hpp"
#include "Ray.hpp"
#include <iostream>

Plane::Plane(Vector3 point, Vector3 normal) : point(point), normal(normal) {}

std::vector<Vector3*> Plane::IntersectPoints(Ray& ray)
{
	std::vector<Vector3*> contactPoints;

	float plane = Vector3::Dot(point, normal);
	float dot1 = plane - Vector3::Dot(ray.origin, normal);
	float dot2 = Vector3::Dot(normal, ray.direction);
	if (dot2 == 0)
	{
		std::cout << "Perpendicular \n";
	}
	else
	{
		float t = dot1 / dot2;
		if (t > 0) 
		{
			contactPoints.push_back(new Vector3(ray.RayStep(t)));
		}
		else {
			std::cout << "-t \n";
		}
	}

	return contactPoints;
}

EIntersectType Plane::Intersect(Ray& ray)
{
	float plane = Vector3::Dot(point, normal);
	float dot1 = plane - Vector3::Dot(ray.origin, normal);
	float dot2 = Vector3::Dot(normal, ray.direction);

	if (dot2 != 0)
	{
		float t = dot1 / dot2;
		if (t > 0)
			return ONE;
	}
	return NONE;
}
