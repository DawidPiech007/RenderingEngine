#pragma once
#include "Vector3.h"

class Intersection
{
public:
	Vector3 point;
	Vector3 normal;
	
	Intersection(Vector3 point, Vector3 normal);
};

