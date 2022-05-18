#pragma once
#include "stb_image.h"
#include "LightIntensity.h"
#include "Vector3.h"

class Texture
{
public:
	Texture(const char* fileName);

	LightIntensity GetColor(int x, int y);
	LightIntensity PlanarUV(Vector3 intersectionPoint, Vector3 meshCenter);

	int width;
	int height;
	int chanels;
	unsigned char* data;
};

