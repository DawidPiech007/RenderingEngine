#pragma once
#include <vector>
#define RENDERER Renderer::GetInstance()


class ICamera;
class Buffer;
class Geometry;

class Renderer
{
private:
	ICamera* camera;
	Buffer* buffer;
public:
	static Renderer& GetInstance();

	Renderer();
	void SetUp(Buffer& buffer, ICamera& camera);


	void BasicRender(std::vector<Geometry*> objects);
	void BasicRender(Geometry& object);
	void Render(std::vector<Geometry*> objects, int antyaliasing = 5);
	void RenderAdaptive(std::vector<Geometry*> objects, int antyaliasing);
	void Render(Geometry& object, int antyaliasing = 5);
	void SetCamera(ICamera& camera);
};
