#pragma once

#include "LightIntensity.hpp"
#include <vector>

#define UP_LEFT 0
#define UP_RIGHT 1
#define DOWN_RIGHT 2
#define DOWN_LEFT 3
#define CENTER 4

class SubPixel
{
public:
	float xMin;
	float xMax;
	float yMin;
	float yMax;
	float weight;

	std::vector<SubPixel*> subPixels;
	std::vector<LightIntensity*> colors;

	SubPixel(float xMin, float xMax, float yMin, float yMax, float weight,
		LightIntensity& colorUL, LightIntensity& colorUR, LightIntensity& colorDR, LightIntensity& colorDL, LightIntensity& colorC);

	SubPixel(float xMin, float xMax, float yMin, float yMax, float weight);

	void CalculateAllCoolr();
};
