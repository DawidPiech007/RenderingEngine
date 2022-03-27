#include "Renderer.hpp"
#include "Buffer.hpp"
#include "Camera.hpp"
#include "Vector3.hpp"
#include "Ray.hpp"
#include "Geometry.hpp"
#include <math.h>
#include <iostream>

using namespace std;

Renderer& Renderer::GetInstance()
{
    static Renderer* instance = nullptr;

    if (instance == nullptr)
        instance = new Renderer();

    return *instance;
}

Renderer::Renderer()
{
}

void Renderer::SetUp(Buffer& buffer, ICamera& camera, float minWeight)
{
    this->buffer = &buffer;
    this->camera = &camera;
    this->minWeight = minWeight;
}

void Renderer::Render(std::vector<Geometry*> objects)
{
    float pixelWitdh = 2.0f / buffer->width;
    float pixelHeight = 2.0f / buffer->height;

    for (int i = 0; i < buffer->width; i++)
    {
        for (int j = 0; j < buffer->height; j++)
        {
            float uMin = (-1.f + i * pixelWitdh) * (camera->GetFOV());
            float uMax = (-1.f + (i + 1.0f) * pixelWitdh) * (camera->GetFOV());

            float vMax = (1.f - j * pixelHeight) * (camera->GetFOV());
            float vMin = (1.f - (j + 1.0f) * pixelHeight) * (camera->GetFOV());

            LightIntensity color = GetColorByAntyalizing(objects, uMin, uMax, vMin, vMax, i, j,
                1.0f, vector<LightIntensity*>{nullptr, nullptr, nullptr, nullptr, nullptr});

            buffer->SetColor(i, j, color);
        }
    }
}

void Renderer::SetCamera(ICamera& camera)
{
    this->camera = &camera;
}

LightIntensity Renderer::GetColorByAntyalizing(vector<Geometry*> objects, float xMin, float xMax, float yMin, float yMax, int xPixel, int yPixel, float weight, vector<LightIntensity*> colors)
{
    LightIntensity outColor(0.0f, 0.0f, 0.0f);

    Ray ray;
    if (colors[UP_LEFT] == nullptr) {
        ray = camera->GetRay(xMin, yMin);
        colors[UP_LEFT] = new LightIntensity(GetColorByRay(objects, ray, xPixel, yPixel));
    }
    if (colors[UP_RIGHT] == nullptr){
        ray = camera->GetRay(xMax, yMin);
        colors[UP_RIGHT] = new LightIntensity(GetColorByRay(objects, ray, xPixel, yPixel));
    }
    if (colors[DOWN_RIGHT] == nullptr) {
        ray = camera->GetRay(xMax, yMax);
        colors[DOWN_RIGHT] = new LightIntensity(GetColorByRay(objects, ray, xPixel, yPixel));
    }
    if (colors[DOWN_LEFT] == nullptr) {
        ray = camera->GetRay(xMin, yMax);
        colors[DOWN_LEFT] = new LightIntensity(GetColorByRay(objects, ray, xPixel, yPixel));
    }
    if (colors[CENTER] == nullptr) {
        ray = camera->GetRay((xMin + xMax) * 0.5f, (yMin + yMax) * 0.5f);
        colors[CENTER] = new LightIntensity(GetColorByRay(objects, ray, xPixel, yPixel));
    }

    if (weight < minWeight || *colors[UP_LEFT] == *colors[CENTER])      // A   o
        outColor += *colors[UP_LEFT];                                   //   B 
    else                                                                // o   o
        outColor += GetColorByAntyalizing(objects, xMin, (xMin + xMax) * 0.5f, yMin, (yMin + yMax) * 0.5f, xPixel, yPixel, weight * 0.5f,
            vector<LightIntensity*>{new LightIntensity(*colors[UP_LEFT]), nullptr, new LightIntensity(*colors[CENTER]), nullptr, nullptr});

    if (weight < minWeight || *colors[UP_RIGHT] == *colors[CENTER])     // o   A
        outColor += *colors[UP_RIGHT];                                  //   B 
    else                                                                // o   o
        outColor += GetColorByAntyalizing(objects, (xMin + xMax) * 0.5f, xMax, yMin, (yMin + yMax) * 0.5f, xPixel, yPixel, weight * 0.5f,
            vector<LightIntensity*>{nullptr, new LightIntensity(*colors[UP_RIGHT]), nullptr, new LightIntensity(*colors[CENTER]), nullptr});

    if (weight < minWeight || *colors[DOWN_RIGHT] == *colors[CENTER])   // o   o
        outColor += *colors[DOWN_RIGHT];                                //   B 
    else                                                                // o   A
        outColor += GetColorByAntyalizing(objects, (xMin + xMax) * 0.5f, xMax, (yMin + yMax) * 0.5f, yMax, xPixel, yPixel, weight * 0.5f,
            vector<LightIntensity*>{ new LightIntensity(*colors[CENTER]), nullptr, new LightIntensity(*colors[DOWN_RIGHT]), nullptr, nullptr});

    if (weight < minWeight || *colors[DOWN_LEFT] == *colors[CENTER])   // o   o
        outColor += *colors[DOWN_LEFT];                                //   B 
    else                                                               // A   o
        outColor += GetColorByAntyalizing(objects, xMin, (xMin + xMax) * 0.5f, (yMin + yMax) * 0.5f, yMax, xPixel, yPixel, weight * 0.5f,
            vector<LightIntensity*>{nullptr, new LightIntensity(*colors[CENTER]), nullptr, new LightIntensity(*colors[DOWN_LEFT]), nullptr});

    for (int i = 0; i < 5; i++){
        delete colors[i];
    }
    colors.clear();

    //if (outColor == LightIntensity())
    //    ;
    //else
    //{
    //    cout << "\nxMin = " << xMin;
    //    cout << "\nxMax = " << xMax;
    //    cout << "\nyMin = " << yMin;
    //    cout << "\nyMax = " << yMax;
    //    cout << "\nColors[UP_LEFT]->r    = " << colors[UP_LEFT]->r;
    //    cout << "\nColors[UP_RIGHT]->r   = " << colors[UP_RIGHT]->r;
    //    cout << "\nColors[DOWN_RIGHT]->r = " << colors[DOWN_RIGHT]->r;
    //    cout << "\nColors[DOWN_LEFT]->r  = " << colors[DOWN_LEFT]->r;
    //    cout << "\nColors[CENTER]->r     = " << colors[CENTER]->r;
    //}

    return outColor * 0.25f; //  outColor / (4 * weight^2 ) ;
}

LightIntensity Renderer::GetColorByRay(std::vector<Geometry*> objects, Ray& ray, int xPixel, int yPixel)
{
    vector<Vector3*> intersectPoints;
    for (int k = 0; k < objects.size(); k++)
    {
        intersectPoints.push_back(objects[k]->IntersectPoint(ray));
    }

    // find object clostes to camera
    int indexMin = -1;
    float distanceMin = std::numeric_limits<float>::max();
    for (int k = 0; k < objects.size(); k++)
    {
        if (intersectPoints[k] != nullptr)
        {
            float distance = (camera->GetPosition() - *intersectPoints[k]).SqrMagnitude();
            if (distance < distanceMin)
            {
                distanceMin = distance;
                indexMin = k;
            }
            delete intersectPoints[k]; // delate pointer
        }
    }
    intersectPoints.clear();

    // add color
    if (indexMin != -1) {
        //cout << "\nindexMin = " << indexMin;
        return objects[indexMin]->baseColor;
    }
    else {
        //cout << "\nbuffer->GetColor(xPixel, yPixel) = " << buffer->GetColor(xPixel, yPixel).r;
        return buffer->GetColor(xPixel, yPixel);
    }
}


