#pragma once

#include "Vector3.hpp"
#include "Buffer.hpp"
#include "Ray.hpp"

class Camera
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;

	Camera();
	Camera(Vector3 position, Vector3 target, Vector3 up = Vector3(0.0f, 1.0f, 0.0f));

	Ray GetRay(float u, float v);
};

