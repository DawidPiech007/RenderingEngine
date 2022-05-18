#include "Texture.h"
#include <iostream>

Texture::Texture(const char* fileName, WrapType wrapType)
{
	this->data = stbi_load(fileName, &this->width, &this->height, &this->chanels , 3);
    this->type = wrapType;
}

LightIntensity Texture::GetColor(int x, int y)
{
	int pixel = (y * width + (height -x)) * 3;
	return LightIntensity(data[pixel] * 0.00392f, data[pixel + 1] * 0.00392f, data[pixel + 2] * 0.00392f);
}

LightIntensity Texture::PlanarUV(Vector3 intersectionPoint, Vector3 meshCenter)
{
    intersectionPoint = intersectionPoint - meshCenter;
    intersectionPoint = Vector3::Normalize(intersectionPoint);
    float u = (intersectionPoint.z + 1) / 2.f;
    float v = (intersectionPoint.x + 1) / 2.f;
    int col = (int)((width -1) * u);
    int row = (int)((height -1) * v);
	return GetColor(row,col);
}

LightIntensity Texture::SphericalUV(Vector3 intersectionPoint, Vector3 meshCenter)
{
    intersectionPoint = intersectionPoint - meshCenter;
    intersectionPoint = Vector3::Normalize(intersectionPoint);
    float theta = acos(intersectionPoint.y);
    float phi = atan2(intersectionPoint.x, intersectionPoint.z);
    if (phi < 0) phi += TWO_PI;

    float u = phi/TWO_PI;
    float v = 1.0 - (theta /PI);
    int col = (int)((width - 1) * v);
    int row = (int)((height - 1) * u);
    return GetColor(row, col);
}

LightIntensity Texture::WrapTexture(Vector3 intersectionPoint, Vector3 meshCenter)
{
    if (type == PLANAR)
        return PlanarUV(intersectionPoint, meshCenter);
    if (type == SPHERICAL)
        return SphericalUV(intersectionPoint, meshCenter);
}
