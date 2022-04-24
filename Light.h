#pragma once

#include <vector>
#include "LightIntensity.h"
#include "Vector3.h"

#define MIN_DISTANCE 0.001f

class Material;
class ICamera;
class Geometry;

class Light
{
public:
	LightIntensity color;

	virtual LightIntensity CaculateColor(Material* material, Vector3 position, Vector3 normal, ICamera* camera);
	virtual bool IsInShadow(Vector3 position, ICamera* camera, std::vector<Geometry*> objects);
};
