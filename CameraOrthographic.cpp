#include "CameraOrthographic.hpp"
#include "Ray.hpp"

CameraOrthographic::CameraOrthographic()
{
	this->position = Vector3(0.0f, 0.0f, 0.0f);
	this->target = Vector3(0.0f, 0.0f, 1.0f);
	this->up = Vector3(0.0f, 1.0f, 0.0f);
}

CameraOrthographic::CameraOrthographic(Vector3 position, Vector3 target, Vector3 up)
{
	this->position = position;
	this->target = target;
	this->up = up;
}

Ray CameraOrthographic::GetRay(float u, float v)
{
    return Ray(Vector3(u, v, 0), target);
}
