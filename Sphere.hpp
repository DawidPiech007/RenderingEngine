#pragma once

#include "Geometry.hpp"

class Sphere: Geometry
{
public:
	Sphere(Vector3& c, float r);
	Sphere();

	Vector3* Intersect(Ray& ray) override;


	Vector3* c; // centrum
	float r;	// dlugosc promienia
};

