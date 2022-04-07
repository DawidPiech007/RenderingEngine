#pragma once

#include <string>
#include <vector>
#include "Geometry.hpp"
#include "Triangle.h"

class Mesh : public Geometry
{
public:
	std::vector<Triangle> triangles;
	int tmpLastUsedTriangleIndex = 0;

	Mesh(std::string path, LightIntensity baseColor);

	Vector3* IntersectPoint(Ray& ray);

	LightIntensity GetColor() override;
};

