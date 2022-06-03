#pragma once

#include <string>

#include "LightIntensity.h"
#include "Texture.h"


enum MaterialType
{
	Refract,
	Reflect,
	Diffuse
};

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
	MaterialType type;

	Material(std::string name = "default", Texture* texture = nullptr, MaterialType type = MaterialType::Diffuse);
	Material(std::string name, MaterialType type);

	void SetValue(float value, std::string type);
	void SetValue(LightIntensity value, std::string type);
};

