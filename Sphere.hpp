#pragma once

#include "Geometry.hpp"
#include "Vector3.hpp"


class Sphere: Geometry
{
public:
	Vector3 center; // centrum
	float radius;	// dlugosc promienia

	Sphere(float cx, float cy, float cz, float r);
	Sphere(Vector3 c, float r);
	Sphere();

	std::vector<Vector3*> IntersectPoints(Ray& ray) override;
	EIntersectType Intersect(Ray& ray) override;

};

