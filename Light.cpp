#include "Light.h"
#include <vector>
#include "Geometry.h"

using namespace std;

LightIntensity Light::CaculateColor(Material* material, Intersection intersection, ICamera* camera, LightIntensity textureColor)
{
	return LightIntensity();
}

bool Light::IsInShadow(Intersection intersection, ICamera* camera, std::vector<Geometry*> objects)
{
	return false;
}
