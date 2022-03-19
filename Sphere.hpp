#pragma once

#include "Geometry.hpp"
#include "Vector3.hpp"


class Sphere: public Geometry
{
public:
	Vector3 center; // centrum
	float radius;	// dlugosc promienia

	Sphere(float cx, float cy, float cz, float r, LightIntensity color = LightIntensity(1.0f,1.0f,1.0f));
	Sphere(Vector3 c, float r, LightIntensity color = LightIntensity(1.0f, 1.0f, 1.0f));
	Sphere();

	std::vector<Vector3*> IntersectPoints(Ray& ray) override;
	EIntersectType Intersect(Ray& ray) override;

};

