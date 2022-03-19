#pragma once
#include "LightIntensity.hpp"

class Buffer
{
public:
	Buffer(int width, int height);

	void FillColor(int r, int g, int b);
	void FillColor(LightIntensity color);
	void FillColorRect(int xMin, int xMax, int yMin, int yMax, int r, int g, int b);
	void FillColorRect(int xMin, int xMax, int yMin, int yMax, LightIntensity color);
	void SetColor(int x, int y, int r, int g, int b);
	void SetColor(int x, int y, LightIntensity color);

	void MakeColoredBackGround();

	int width;
	int height;
	int lenght;
	unsigned char* data;
};

