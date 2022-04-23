#include "CameraOrthographic.h"
#include "Ray.h"

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

Vector3 CameraOrthographic::GetPosition()
{
	return position;
}

Vector3 CameraOrthographic::GetTarget()
{
	return target;
}

Vector3 CameraOrthographic::GetUp()
{
	return up;
}

Ray CameraOrthographic::GetRay(float u, float v)
{
    return Ray(Vector3(u, v, 0), target);
}

/*
For CameraOrthographic always return 1
*/
float CameraOrthographic::GetFOV()
{
	return 1;
}