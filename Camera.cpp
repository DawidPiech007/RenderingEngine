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
