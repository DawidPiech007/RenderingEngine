#include "Texture.h"


Texture::Texture(const char* fileName)
{
	this->data = stbi_load(fileName, &this->width, &this->height, &this->chanels , 3);
}

LightIntensity Texture::GetColor(int x, int y)
{
	int pixel = (y * width + x) * 3;
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


//todo delete pointers