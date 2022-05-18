#pragma once

#include "Geometry.h"
#include "Vector3.h"


class Sphere: public Geometry
{
public:
	//Vector3 center; // centrum
	float radius;	// dlugosc promienia

	Sphere(float cx, float cy, float cz, float r);
	Sphere(Vector3 c, float r, Material* material);
	Sphere(Vector3 c, float r);
	Sphere();

	Intersection* GetIntersection(Ray& ray, bool backsidedClipping = true) override;
};

