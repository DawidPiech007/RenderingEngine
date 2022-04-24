#include "PointLight.h"
#include "Material.h"
#include "Geometry.h"
#include "Ray.h"
#include "Camera.h"
#include <vector>
#include <iostream>

using namespace std;

PointLight::PointLight()
{
	this->color = LightIntensity();
	this->lightPos = Vector3();
	this->constAtten = 1.0f;
	this->linearAtten = 1.0f;
	this->quadAtten = 1.0f;
}

PointLight::PointLight(LightIntensity color, Vector3 lightPos, float constAtten, float linearAtten, float quadAtten)
{
	this->color = color;
	this->lightPos = lightPos;
	this->constAtten = constAtten;
	this->linearAtten = linearAtten;
	this->quadAtten = quadAtten;
}

LightIntensity PointLight::CaculateColor(Material* material, Vector3 position, Vector3 normal, ICamera* camera)
{
	return material->diffuse * color;
}

bool PointLight::IsInShadow(Vector3 position, ICamera* camera, std::vector<Geometry*> objects)
{
    //Ray ray = Ray(position, position- lightPos);
    Ray ray = Ray(position, lightPos - position);

    vector<Vector3*> intersectPoints;
    for (int k = 0; k < objects.size(); k++)
    {
        intersectPoints.push_back(objects[k]->IntersectPoint(ray));
    }

    // find object clostes to camera
    int indexMin = -1;
    float distanceMin = (lightPos - position).Magnitude(); // szukamy punktu przeciêcia w odleg³oœci mniejszej ni¿ odleg³oœæ od œwiat³a

    for (int k = 0; k < objects.size(); k++)
    {
        if (intersectPoints[k] != nullptr)
        {
            float distance = (camera->GetPosition() - *intersectPoints[k]).Magnitude();
            if (distance < distanceMin/* && distance> MIN_DISTANCE*/)
            {
                distanceMin = distance;
                indexMin = k;
            }
            delete intersectPoints[k]; // delate pointer
        }
    }
    intersectPoints.clear();

    if (indexMin == -1)
	    return false;

    return true;
}
