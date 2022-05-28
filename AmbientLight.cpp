#include "AmbientLight.h"
#include "Material.h"
#include "Intersection.h"


AmbientLight::AmbientLight()
{
	color = LightIntensity(0.0f, 0.0f, 0.0f);
}

AmbientLight::AmbientLight(LightIntensity color)
{
	this->color = color;
}

LightIntensity AmbientLight::CaculateColor(Material* material, Intersection intersection, ICamera* camera, LightIntensity textureColor)
{

	return material->ambient * color * textureColor;
}

bool AmbientLight::IsInShadow(Intersection intersection, ICamera* camera, std::vector<Geometry*> objects)
{
	return false;
}
