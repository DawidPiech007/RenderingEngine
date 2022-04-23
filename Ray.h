#pragma once
#include "Vector3.h"
class Ray
{
public:
	Vector3 origin;
	Vector3 direction;
	Vector3 destination;
	
	float distance;

	Ray();
	Ray(Vector3 origin, Vector3 direction);
	
	Vector3 RayStep(float t);
};

