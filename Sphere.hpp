#pragma once

#include "Geometry.hpp"

class Sphere: Geometry
{
public:
	Vector3* c; // centrum
	float r;	// dlugosc promienia

	Sphere(float cx, float cy, float cz, float r);
	Sphere(Vector3& c, float r);
	Sphere();

	std::list<Vector3*> Intersect(Ray& ray) override;


};

