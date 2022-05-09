#pragma once

#include <vector>
#include "LightIntensity.h"
#include "Material.h"
#include "Intersection.h"

// predekralacje klas 
class Vector3;
class Ray;

class Geometry
{
public:
	Material* material;

	Geometry();
	Geometry(Material& material);

	virtual Intersection* GetIntersection(Ray& ray, bool backsidedClipping = true);
};

