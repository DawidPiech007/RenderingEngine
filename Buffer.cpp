#include "Buffer.hpp"
#include "LightIntensity.hpp"

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

void Buffer::FillColorRect(int r, int g, int b, int xMin, int xMax, int yMin, int yMax)
{
	for (int y = yMin; y < yMax; y++)
	{
		for (int x = xMin; x < xMax; x++)
		{
			SetColor(x, y, r, g, b);
		}
	}
}

void Buffer::SetColor(int x, int y, int r, int g, int b)
{
	int pixel = (y * width + x) * 3;
	data[pixel] = r;
	data[pixel + 1] = g;
	data[pixel + 2] = b;
}

void Buffer::MakeColoredBackGround()
{
	int row = 6;
	int col = 6;
	LightIntensity startColor[6] = { {0.1f,0.0f,0.0f}, {0.0f,0.1f,0.0f}, {0.0f,0.0f,0.1f},
	{1.0f,0.0f,0.0f}, {0.0f,1.0f,0.0f}, {1.0f,1.0f,0.0f} }; 
	LightIntensity endColor[6] = { {1.0f,0.0f,0.0f}, {0.0f,1.0f,0.0f}, {0.0f,0.0f,1.0f},
	{1.0f,0.0f,1.0f}, {0.0f,1.0f,1.0f}, {1.0f,1.0f,1.0f} };

	int recSizeX = (width / col);
	int recSizeY = (height / row);

	for (int i = 0; i < col; i++)
	{
		for (float j = 0; j < row; j++)
		{
			LightIntensity color = startColor[i] + (endColor[i] - startColor[i]) * (j / row);
			
			int xMin = recSizeX * i;
			int xMax = xMin + recSizeX;
			int yMin = recSizeY * j;
			int yMax = yMin + recSizeY;

			FillColorRect(color.r * 255, color.g * 255, color.b * 255, xMin, xMax, yMin, yMax);
		}
	}
}
