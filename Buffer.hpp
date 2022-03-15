#pragma once
class Buffer
{
public:
	Buffer(int width, int height);

	void FillColor(int r, int g, int b);
	void SetColor(int x, int y, int r, int g, int b);

	int width;
	int height;
	int lenght;
	unsigned char* data;
};

