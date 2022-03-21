#pragma once
#include "ICamera.hpp"
#include "Ray.hpp"

class CameraOrthographic : public ICamera
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;

	CameraOrthographic();
	CameraOrthographic(Vector3 position, Vector3 target = Vector3(0.0f, 0.0f, 1.0f), Vector3 up = Vector3(0.0f, 1.0f, 0.0f));

	Ray GetRay(float u, float v) override;

private:
	float GetFOV() override;
};

