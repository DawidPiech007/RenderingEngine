#include "SubPixel.hpp"

SubPixel::SubPixel(float xMin, float xMax, float yMin, float yMax, float weight,
	LightIntensity& colorUL, LightIntensity& colorUR, LightIntensity& colorDR, LightIntensity& colorDL, LightIntensity& colorC)
{
	this->xMin = xMin;
	this->xMax = xMax;
	this->yMin = yMin;
	this->yMax = yMax;
	this->weight = weight;

	colors.push_back(&colorUL);
	colors.push_back(&colorUR);
	colors.push_back(&colorDR);
	colors.push_back(&colorDL);
	colors.push_back(&colorC);

	for (int i = 0; i < 4; i++)
		subPixels.push_back(nullptr);
}

SubPixel::SubPixel(float xMin, float xMax, float yMin, float yMax, float weight)
{
	this->xMin = xMin;
	this->xMax = xMax;
	this->yMin = yMin;
	this->yMax = yMax;
	this->weight = weight;

	for (int i = 0; i < 5; i++)
		colors.push_back(nullptr);

	for (int i = 0; i < 4; i++)
		subPixels.push_back(nullptr);
}

void SubPixel::CalculateAllCoolr()
{

}
