#include "Light.h"
#include <vector>
#include "Geometry.h"

using namespace std;

LightIntensity Light::CaculateColor(Material* material, Vector3 position, Vector3 normal, ICamera* camera)
{
	return LightIntensity();
}

bool Light::IsInShadow(Vector3 position, ICamera* camera, std::vector<Geometry*> objects)
{
	return false;
}
