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

	Vector3 center;
	float r;

	Mesh();

	void SetUp();

	Intersection* GetIntersection(Ray& ray, bool backsidedClipping = true) override;
};

