#pragma once
#include "Light.h"

class AmbientLight : public Light
{
public:
	AmbientLight();
	AmbientLight(LightIntensity color);

	LightIntensity CaculateColor(Material* material, Vector3 position, Vector3 normal, ICamera* camera) override;
	bool IsInShadow(Vector3 position, ICamera* camera, std::vector<Geometry*> objects) override;
};

