#pragma once

#include <string>
#include <vector>
#include "Geometry.hpp"
#include "Triangle.h"

class Mesh : public Geometry
{
public:
	std::vector<Triangle> triangles;

	Mesh(std::string path, LightIntensity baseColor);

	Vector3* IntersectPoint(Ray& ray);
};

