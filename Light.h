#pragma once

#include <vector>
#include "LightIntensity.h"
#include "Vector3.h"

#define TRIANGLE_OFFSET 0.1f

class Material;
class ICamera;
class Geometry;
class Intersection;

class Light
{
public:
	LightIntensity color;

	virtual LightIntensity CaculateColor(Material* material, Intersection intersection,ICamera* camera);
	virtual bool IsInShadow(Intersection intersection, ICamera* camera, std::vector<Geometry*> objects);
};
