#pragma once

#include <vector>
#include "LightIntensity.h"
// predekralacje klas 
class Vector3;
class Ray;

enum EIntersectType
{
	NONE,
	ONE,
	TWO,
	INF
};

class Geometry
{
public:
	LightIntensity baseColor;

	Geometry();
	Geometry(LightIntensity baseColor);

	virtual std::vector<Vector3*> IntersectPoints(Ray& ray);
	virtual Vector3* IntersectPoint(Ray& ray);
	virtual EIntersectType Intersect(Ray& ray);
	virtual LightIntensity GetColor();
};

