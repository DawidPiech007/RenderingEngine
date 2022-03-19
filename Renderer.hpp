#pragma once
#include <vector>

class Camera;
class Buffer;
class Geometry;

class Renderer
{
public:
	Camera* camera;
	Buffer* buffer;

	Renderer(Buffer& buffer, Camera& camera);

	void BasicRender(std::vector<Geometry*> objects);
	void BasicRender(Geometry& object);
	void PerspectiveRender(std::vector<Geometry*> objects);
	void PerspectiveRender(Geometry& object);
};

