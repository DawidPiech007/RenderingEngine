#pragma once

#include <vector>
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
	virtual std::vector<Vector3*> IntersectPoints(Ray& ray);
	virtual EIntersectType Intersect(Ray& ray);
};

