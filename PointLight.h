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

	LightIntensity CaculateColor(Material* material, Intersection intersection, ICamera* camera, LightIntensity textureColor) override;
	bool IsInShadow(Intersection intersection, ICamera* camera, std::vector<Geometry*> objects) override;
};

