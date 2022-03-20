#include "Camera.hpp"

Camera::Camera()
{
	this->position = Vector3(0.0f, 0.0f, 0.0f);
	this->target = Vector3(0.0f, 0.0f, -1.0f);
	this->up = Vector3(0.0f, 1.0f, 0.0f);
}

Camera::Camera(Vector3 position, Vector3 target, Vector3 up)
{
	this->position = position;
	this->target = target;
	this->up = up;
}

Ray Camera::GetRay(float u, float v)
{
	Vector3 rayDirection = Vector3(u, v, 0) - Vector3(target);
	rayDirection = rayDirection.Normalize();
	return  Ray(Vector3(position), rayDirection);
}
