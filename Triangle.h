#pragma once
#include "Geometry.hpp"
#include "Vector3.hpp"

class Triangle: public Geometry
{
public:

	Vector3 v1, v2, v3;

	Triangle();
	Triangle(Vector3 v1, Vector3 v2, Vector3 v3, LightIntensity baseColor);

	std::vector<Vector3*> IntersectPoints(Ray& ray);
	Vector3* IntersectPoint(Ray& ray);
	EIntersectType Intersect(Ray& ray);
};

