#pragma once
#include "stb_image.h"
#include "LightIntensity.h"

class Texture
{
public:
	Texture(const char* fileName);

	LightIntensity GetColor(int x, int y);

	int width;
	int height;
	int chanels;
	unsigned char* data;
};

