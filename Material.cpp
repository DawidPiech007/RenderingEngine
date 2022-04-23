#include "Material.h"

Material::Material(std::string name)
{
	this->name = name;
}

void Material::SetValue(float value, std::string type)
{
	if (type == "Ns")
		this->shinines = value;
	else if (type == "d")
		this->transparency = value;
}

void Material::SetValue(LightIntensity value, std::string type)
{
	if (type == "Ka")
		this->ambient = value;
	else if (type == "Kd")
		this->diffuse = value;
	else if (type == "Ks")
		this->specular = value;
}
