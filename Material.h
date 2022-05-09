#pragma once

#include <string>

#include "LightIntensity.h"

class Material
{
public:
	std::string name; // newmtl
	LightIntensity ambient; // Ka
	LightIntensity diffuse; // Kd
	LightIntensity specular; // Ks
	float shinines; // Ns
	float transparency; // d

	Material(std::string name = "default");

	void SetValue(float value, std::string type);
	void SetValue(LightIntensity value, std::string type);
};

