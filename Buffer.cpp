#include "Buffer.hpp"

Buffer::Buffer(int width, int height) : width(width), height(height)
{
	lenght = width * height;
	data = new unsigned char[lenght * 3];
}

void Buffer::FillColor(int r, int g, int b)
{
	for (int i = 0; i < lenght; i++)
	{
		data[i * 3] = r;		// R
		data[i * 3 + 1] = g;	// G
		data[i * 3 + 2] = b;	// B
	}
}

void Buffer::SetColor(int x, int y, int r, int g, int b)
{
	int pixel = (y * width + x) * 3;
	data[pixel] = r;
	data[pixel + 1] = g;
	data[pixel + 2] = b;
}
