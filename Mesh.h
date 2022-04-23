#pragma once

#include <string>
#include <vector>
#include "Geometry.h"
#include "Triangle.h"
#include "Material.h"

class Mesh : public Geometry
{
public:
	std::vector<Triangle> triangles;
	int tmpLastUsedTriangleIndex = 0;
	Material* material;

	Mesh();
	Mesh(std::string path, LightIntensity baseColor);

	Vector3* IntersectPoint(Ray& ray);

	LightIntensity GetColor() override;
};

