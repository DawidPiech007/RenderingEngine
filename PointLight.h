#pragma once
#include "Light.h"

class PointLight : public Light
{
public:
	Vector3 lightPos;
	float constAtten;
	float linearAtten;
	float quadAtten;

	PointLight();
	PointLight(LightIntensity color, Vector3 lightPos, float constAtten, float linearAtten, float quadAtten);

	LightIntensity CaculateColor(Material* material, Vector3 position, Vector3 normal, ICamera* camera) override;
	bool IsInShadow(Vector3 position, ICamera* camera, std::vector<Geometry*> objects) override;
};

