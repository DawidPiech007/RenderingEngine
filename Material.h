#pragma once

#include <string>

#include "LightIntensity.h"
#include "Texture.h"

class Material
{
public:
	std::string name; // newmtl
	LightIntensity ambient; // Ka
	LightIntensity diffuse; // Kd
	LightIntensity specular; // Ks
	float shinines; // Ns
	float transparency; // d
	Texture* texture;

	Material(std::string name = "default", Texture* texture = nullptr);

	void SetValue(float value, std::string type);
	void SetValue(LightIntensity value, std::string type);
};

