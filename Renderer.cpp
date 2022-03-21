#include "Renderer.hpp"
#include "Buffer.hpp"
#include "Camera.hpp"
#include "Vector3.hpp"
#include "Ray.hpp"
#include "Geometry.hpp"
#include <math.h>

Renderer::Renderer(Buffer& buffer, ICamera& camera)
{
	this->buffer = &buffer;
	this->camera = &camera;
}

void Renderer::BasicRender(std::vector<Geometry*> objects)
{
	for (int i = 0; i < objects.size(); i++)
	{
		BasicRender(*objects[i]);
	}
}

void Renderer::BasicRender(Geometry& object)
{
    float pixelWitdh = 2.0f / buffer->width;
    float pixelHeight = 2.0f / buffer->height;

    for (int i = 0; i < buffer->width; i++)
    {
        for (int j = 0; j < buffer->height; j++)
        {
            float midX = (-1.f + (i + 0.5f) * pixelHeight);
            float midY = 1.f - (j + 0.5f) * pixelWitdh;

            Ray ray = camera->GetRay(midX, midY);
            EIntersectType intersect = object.Intersect(ray);
            if (intersect != EIntersectType::NONE) {
                buffer->SetColor(i, j, object.baseColor);
            }
        }
    }
}


void Renderer::Render(std::vector<Geometry*> objects, int antyaliasing)
{
    for (int i = 0; i < objects.size(); i++)
    {
        Render(*objects[i],antyaliasing);
    }
}

void Renderer::Render(Geometry& object, int antyaliasing)
{
    float pixelWitdh = 2.0f / buffer->width;
    float pixelHeight = 2.0f / buffer->height;

    float pixelAntyaliasingWitdh = pixelWitdh / antyaliasing;
    float pixelAntyaliasingHeight = pixelHeight / antyaliasing;
    float pixelAntyaliasingOffsetX = (antyaliasing - 1) * 0.5f;
    float pixelAntyaliasingOffsetY = (antyaliasing - 1) * 0.5f;

    for (int i = 0; i < buffer->width; i++)
    {
        for (int j = 0; j < buffer->height; j++)
        {
            float uMain = (-1.f + (i + 0.5f) * pixelHeight) * (camera->GetFOV());
            float vMain = (1.f - (j + 0.5f) * pixelWitdh) * (camera->GetFOV());

            LightIntensity color = LightIntensity(0.0f, 0.0f, 0.0f);

            for (int x = 0; x < antyaliasing; x++)
            {
                for (int y = 0; y < antyaliasing; y++)
                {
                    float u = uMain + (y - pixelAntyaliasingOffsetY) * pixelAntyaliasingHeight;
                    float v = vMain + (x - pixelAntyaliasingOffsetX) * pixelAntyaliasingWitdh;

                    Ray ray = camera->GetRay(u, v);
                    EIntersectType intersect = object.Intersect(ray);

                    if (intersect != EIntersectType::NONE) {
                        color += object.baseColor;
                    }
                    else{
                        color += buffer->GetColor(i, j);
                    }
                }
            }

            buffer->SetColor(i, j, color / (antyaliasing * antyaliasing));
        }
    }
}

void Renderer::SetCamera(ICamera& camera)
{
    this->camera = &camera;
}
