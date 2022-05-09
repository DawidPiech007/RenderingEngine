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

	Intersection* GetIntersection(Ray& ray, bool backsidedClipping = true) override;
};

