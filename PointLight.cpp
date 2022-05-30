#include "PointLight.h"
#include "Material.h"
#include "Geometry.h"
#include "Ray.h"
#include "Camera.h"
#include "Renderer.h"
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

LightIntensity PointLight::CaculateColor(Material* material, Intersection intersection, ICamera* camera, LightIntensity textureColor)
{
    LightIntensity outColor = LightIntensity(0.0f, 0.0f, 0.0f);

    Vector3 dir = intersection.point - lightPos;
    float distance = dir.Magnitude();
    dir = dir.Normalize();

    //diffuse
    float kd = Vector3::Dot(intersection.normal, -dir);
    if (kd < 0.0f)
        kd = 0.0f;

    //specular
    Vector3 viewDir = RENDERER.GetCanera()->GetPosition() - intersection.point;
    viewDir = viewDir.Normalize();
    Vector3 reflectDir = Vector3::Reflect(dir, intersection.normal);
    float ks = Vector3::Dot(viewDir, reflectDir);
    if (ks < 0)
        ks = 0.0f;
    else
        ks = pow(ks, material->shinines);

    outColor += material->diffuse * kd * textureColor + material->specular * ks * textureColor;

    float atten = 1.0f / (constAtten + distance * linearAtten + distance * distance * quadAtten);
    //cout << atten << endl;
    outColor *= atten;

    if (outColor.r > 1.0f)    outColor.r = 1.0f;
    if (outColor.g > 1.0f)    outColor.g = 1.0f;
    if (outColor.b > 1.0f)    outColor.b = 1.0f;

    return outColor;
}

bool PointLight::IsInShadow(Intersection intersection, ICamera* camera, std::vector<Geometry*> objects)
{
    //Ray ray = Ray(position, position- lightPos);
    Vector3 pointOffset = intersection.point + intersection.normal * TRIANGLE_OFFSET;

    Ray ray = Ray(pointOffset, lightPos - pointOffset);

    vector<Intersection*> intersections;
    for (int k = 0; k < objects.size(); k++)
    {
        intersections.push_back(objects[k]->GetIntersection(ray, false));
    }

    // find object clostes to ray origin
    int indexMin = -1;
    float distanceMin = (lightPos - pointOffset).Magnitude(); // szukamy punktu przeciêcia w odleg³oœci mniejszej ni¿ odleg³oœæ od œwiat³a

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
