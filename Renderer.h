#pragma once
#include <vector>
#include "LightIntensity.h"

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
class Light;

class Renderer
{
private:
	ICamera* camera;
	Buffer* buffer;
	float minWeight;// antialaizing
	Renderer() {};
public:
	static Renderer& GetInstance();

	
	void SetUp(Buffer& buffer, ICamera& camera, float minWeight);

	void Render(std::vector<Geometry*> objects, std::vector<Light*> lights);
	void RenderNoAntiAliasing(std::vector<Geometry*> objects, std::vector<Light*> lights);

	void SetCamera(ICamera& camera);

	ICamera* GetCanera();

	int maxReyPath = 10;

private:
	LightIntensity GetColorByAntyalizing(std::vector<Geometry*> objects, std::vector<Light*> lights, float xMin, float xMax, float yMin, float yMax,
		int xPixel, int yPixel, float weight, std::vector<LightIntensity*> colors);

	LightIntensity GetColorByRay(std::vector<Geometry*> objects, std::vector<Light*> lights, Ray& ray, int xPixel, int yPixel, int rayDepth = 0);

};
