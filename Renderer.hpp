#pragma once
#include <vector>

class ICamera;
class Buffer;
class Geometry;

class Renderer
{
private:
	ICamera* camera;
	Buffer* buffer;
public:

	Renderer(Buffer& buffer, ICamera& camera);

	void BasicRender(std::vector<Geometry*> objects);
	void BasicRender(Geometry& object);
	void Render(std::vector<Geometry*> objects, int antyaliasing = 5);
	void Render(Geometry& object, int antyaliasing = 5);
	void SetCamera(ICamera& camera);
};
