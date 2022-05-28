#pragma once
#include "Light.h"

class AmbientLight : public Light
{
public:
	AmbientLight();
	AmbientLight(LightIntensity color);

	LightIntensity CaculateColor(Material* material, Intersection intersection, ICamera* camera, LightIntensity textureColor) override;
	bool IsInShadow(Intersection intersection, ICamera* camera, std::vector<Geometry*> objects) override;
};

