#pragma once
class Vector3;
class Ray;

class ICamera
{
public:

	virtual Vector3 GetPosition();
	virtual Vector3 GetTarget();
	virtual Vector3 GetUp();
	virtual Ray GetRay(float u, float v);
	virtual float GetFOV();
};

