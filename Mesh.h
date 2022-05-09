#pragma once

#include <string>
#include <vector>
#include "Geometry.h"
#include "Triangle.h"

class Mesh : public Geometry
{
public:
	std::vector<Triangle> triangles;
	int tmpLastUsedTriangleIndex = 0;

	Mesh();

	Intersection* GetIntersection(Ray& ray, bool backsidedClipping = true) override;
};

