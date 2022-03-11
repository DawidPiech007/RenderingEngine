#pragma once

#include <list>
// predekralacje klas 
class Vector3;
class Ray;

class Geometry
{
public:
	virtual std::list<Vector3*> Intersect(Ray& ray);
};

