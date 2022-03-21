#pragma once
class Vector3;
class Ray;

class ICamera
{
public:

	virtual Ray GetRay(float u, float v);
	virtual float GetFOV();
};

