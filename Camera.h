#pragma once
#define PI 3.14159265

#include "Buffer.h"
#include "Ray.h"
#include "ICamera.h"

class Camera: public ICamera
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;
	float fov; //field of view
	float nearPlane;
	float farPlane;

	Camera();
	Camera(Vector3 position, Vector3 target = Vector3(0.0f, 0.0f, 1.0f), Vector3 up = Vector3(0.0f, 1.0f, 0.0f));

	Vector3 GetPosition() override;
	Vector3 GetTarget() override;
	Vector3 GetUp() override;
	Ray GetRay(float u, float v) override;
	float GetFOV() override;

	void SetFOV(float angle);
};

