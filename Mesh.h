#pragma once

#include <string>
#include <vector>
#include "Geometry.h"
#include "Triangle.h"
#include "Sphere.h"

class Mesh : public Geometry
{
public:
	std::vector<Triangle> triangles;
	int tmpLastUsedTriangleIndex = 0;
	Sphere boundingSphere;

	void SetUp();
	Mesh();

	Intersection* GetIntersection(Ray& ray, bool backsidedClipping = true) override;
};

