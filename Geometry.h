#pragma once

#include <vector>
#include "LightIntensity.h"
#include "Material.h"
#include "Intersection.h"
#include "Ray.h"
#include "Vector3.h"

class Geometry
{
public:
	Vector3 center;
	Material* material;

	Geometry();
	Geometry(Material& material);

	virtual Intersection* GetIntersection(Ray& ray, bool backsidedClipping = true);
};

