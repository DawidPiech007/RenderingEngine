#pragma once
#include "stb_image.h"
#include "LightIntensity.h"
#include "Vector3.h"

#define PI 3.14159265
#define TWO_PI 6.2831853

enum WrapType
{
	PLANAR,
	SPHERICAL
};

class Texture
{
public:
	Texture(const char* fileName, WrapType wrapType);

	LightIntensity GetColor(int x, int y);
	LightIntensity PlanarUV(Vector3 intersectionPoint, Vector3 meshCenter);
	LightIntensity SphericalUV(Vector3 intersectionPoint, Vector3 meshCenter);
	LightIntensity WrapTexture(Vector3 intersectionPoint, Vector3 meshCenter);

	WrapType type;
	int width;
	int height;
	int chanels;
	unsigned char* data;
};

