#include "AmbientLight.h"
#include "Material.h"


AmbientLight::AmbientLight()
{
	color = LightIntensity(0.0f, 0.0f, 0.0f);
}

AmbientLight::AmbientLight(LightIntensity color)
{
	this->color = color;
}

LightIntensity AmbientLight::CaculateColor(Material* material, Vector3 position, Vector3 normal, ICamera* camera)
{
	return material->ambient * color;
}

bool AmbientLight::IsInShadow(Vector3 position, ICamera* camera, std::vector<Geometry*> objects)
{
	return false;
}
