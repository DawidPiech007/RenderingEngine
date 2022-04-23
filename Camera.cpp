#include "Camera.h"

Camera::Camera()
{
	this->position = Vector3(0.0f, 0.0f, 0.0f);
	this->target = Vector3(0.0f, 0.0f, 1.0f);
	this->up = Vector3(0.0f, 1.0f, 0.0f);
	this->nearPlane = 0;
	this->farPlane = 100;
	fov = 90;
}

Camera::Camera(Vector3 position, Vector3 target, Vector3 up)
{
	this->position = position;
	this->target = target;
	this->up = up;
	fov = 90;
}

Vector3 Camera::GetPosition()
{
	return position;
}

Vector3 Camera::GetTarget()
{
	return target;
}

Vector3 Camera::GetUp()
{
	return up;
}

Ray Camera::GetRay(float u, float v)
{
	Vector3 rayDirection = Vector3(u, v, 0) + Vector3(target);
	rayDirection = rayDirection.Normalize();
	return  Ray(Vector3(position), rayDirection);
}

/*
* Return fov in radians
*/
float Camera::GetFOV()
{
	return ((this->fov/2.f) * PI / 180.f);
}

/*
* Set FOV angle in degrees
*/
void Camera::SetFOV(float angle)
{
	this->fov = angle;
}
