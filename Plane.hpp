#pragma once
#include "Geometry.hpp"
#include "Vector3.hpp"
#include <vector>

class Plane: public Geometry
{
public:

	Vector3 point;
	Vector3 normal;

	Plane(Vector3 point, Vector3 normal);

	std::vector<Vector3*> IntersectPoints(Ray& ray) override;
	EIntersectType Intersect(Ray& ray) override;
};

