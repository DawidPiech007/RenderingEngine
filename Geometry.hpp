#pragma once

#include <vector>
// predekralacje klas 
class Vector3;
class Ray;

class Geometry
{
public:
	virtual std::vector<Vector3*> Intersect(Ray& ray);
};

