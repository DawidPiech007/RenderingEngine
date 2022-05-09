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

LightIntensity PointLight::CaculateColor(Material* material, Intersection intersection, ICamera* camera)
{
    return material->diffuse * color;
}

bool PointLight::IsInShadow(Intersection intersection, ICamera* camera, std::vector<Geometry*> objects)
{
    //Ray ray = Ray(position, position- lightPos);
    Ray ray = Ray(intersection.point + intersection.normal * TRIANGLE_OFFSET, lightPos - intersection.point);

    vector<Intersection*> intersections;
    for (int k = 0; k < objects.size(); k++)
    {
        intersections.push_back(objects[k]->GetIntersection(ray, false));
    }

    // find object clostes to ray origin
    int indexMin = -1;
    float distanceMin = (lightPos - intersection.point).Magnitude(); // szukamy punktu przeciêcia w odleg³oœci mniejszej ni¿ odleg³oœæ od œwiat³a

    for (int k = 0; k < objects.size(); k++)
    {
        if (intersections[k] != nullptr)
        {
            float distance = (ray.origin - intersections[k]->point).Magnitude();
            if (distance < distanceMin)
            {
                distanceMin = distance;
                indexMin = k;
            }
            delete intersections[k]; // delate pointer
        }
    }
    intersections.clear();

    if (indexMin == -1)
        return false;

    return true;
}
