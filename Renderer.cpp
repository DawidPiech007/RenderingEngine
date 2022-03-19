#include "Renderer.hpp"
#include "Buffer.hpp"
#include "Camera.hpp"
#include "Vector3.hpp"
#include "Ray.hpp"
#include "Geometry.hpp"

Renderer::Renderer(Buffer& buffer, Camera& camera)
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
            float midX = -1.f + (i + 0.5f) * pixelHeight;
            float midY = 1.f - (j + 0.5f) * pixelWitdh;

            Ray ray(Vector3(midX, midY, 0), Vector3(0, 0, 1));
            EIntersectType intersect = object.Intersect(ray);
            if (intersect != EIntersectType::NONE) {
                buffer->SetColor(i, j, object.baseColor);
            }
        }
    }
}

void Renderer::PerspectiveRender(std::vector<Geometry*> objects)
{
    for (int i = 0; i < objects.size(); i++)
    {
        PerspectiveRender(*objects[i]);
    }
}

void Renderer::PerspectiveRender(Geometry& object)
{
    float pixelWitdh = 2.0f / buffer->width;
    float pixelHeight = 2.0f / buffer->height;

    for (int i = 0; i < buffer->width; i++)
    {
        for (int j = 0; j < buffer->height; j++)
        {
            float u = -1.f + (i + 0.5f) * pixelHeight;
            float v = 1.f - (j + 0.5f) * pixelWitdh;

            Vector3 rayDirection = Vector3(u, v, 0) - Vector3(camera->target);
            rayDirection = rayDirection.Normalize();
            Ray ray(Vector3(camera->position), rayDirection);
            EIntersectType intersect = object.Intersect(ray);
            if (intersect != EIntersectType::NONE) {
                buffer->SetColor(i, j, object.baseColor);
            }
        }
    }
}
