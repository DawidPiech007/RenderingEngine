#pragma once
class Buffer
{
public:
	Buffer(int width, int height);

	void FillColor(int r, int g, int b);
	void FillColorRect(int r, int g, int b, int xMin, int xMax, int yMin, int yMax);
	void SetColor(int x, int y, int r, int g, int b);

	void MakeColoredBackGround();

	int width;
	int height;
	int lenght;
	unsigned char* data;
};

