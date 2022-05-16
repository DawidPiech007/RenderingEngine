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


//todo delete pointers