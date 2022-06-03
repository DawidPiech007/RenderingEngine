#include "Material.h"

Material::Material(std::string name, Texture* texture, MaterialType type)
{
	this->name = name;
	this->type = type;
	diffuse = LightIntensity(1.0f, 1.0f, 1.0f);
	ambient = LightIntensity(1.0f, 1.0f, 1.0f);
	specular = LightIntensity(1.0f, 1.0f, 1.0f);
	shinines = 32.0f;
	transparency = 1.0f;

	if (texture != nullptr)
		this->texture = texture;
}

Material::Material(std::string name, MaterialType type)
{
	this->name = name;
	this->type = type;
	diffuse = LightIntensity(1.0f, 1.0f, 1.0f);
	ambient = LightIntensity(1.0f, 1.0f, 1.0f);
	specular = LightIntensity(1.0f, 1.0f, 1.0f);
	shinines = 32.0f;
	transparency = 1.0f;
	this->texture = nullptr;
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
