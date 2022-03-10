#pragma once

// predekralacje klas 
class Vector3;
class Ray;

class Geometry
{
public:
	virtual Vector3* Intersect(Ray& ray);
};

