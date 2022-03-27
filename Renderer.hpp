#pragma once
#include <vector>
#include "LightIntensity.hpp"
#define RENDERER Renderer::GetInstance()

#define UP_LEFT 0
#define UP_RIGHT 1
#define DOWN_RIGHT 2
#define DOWN_LEFT 3
#define CENTER 4

class ICamera;
class Buffer;
class Geometry;
class Ray;

class Renderer
{
private:
	ICamera* camera;
	Buffer* buffer;
	float minWeight;// antialaizing
public:
	static Renderer& GetInstance();

	Renderer();
	void SetUp(Buffer& buffer, ICamera& camera, float minWeight);

	void Render(std::vector<Geometry*> objects);
	void RenderNoAntiAliasing(std::vector<Geometry*> objects);

	void SetCamera(ICamera& camera);

private:
	LightIntensity GetColorByAntyalizing(std::vector<Geometry*> objects, float xMin, float xMax, float yMin, float yMax,
		int xPixel, int yPixel, float weight, std::vector<LightIntensity*> colors);

	LightIntensity GetColorByRay(std::vector<Geometry*> objects, Ray& ray, int xPixel, int yPixel);

};
