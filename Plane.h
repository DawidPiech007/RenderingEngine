#pragma once
#include "Geometry.h"
#include "Vector3.h"
#include <vector>

class Plane: public Geometry
{
public:

	Vector3 point;
	Vector3 normal;

	Plane(Vector3 point, Vector3 normal);

	Plane(Vector3 point, Vector3 normal, LightIntensity color);

	std::vector<Vector3*> IntersectPoints(Ray& ray) override;
	Vector3* IntersectPoint(Ray& ray) override;
	EIntersectType Intersect(Ray& ray) override;
};

