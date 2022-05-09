#pragma once
#include "Geometry.h"
#include "Vector3.h"
#include "Vector2.h"

class Triangle: public Geometry
{
public:

	Vector3 v1, v2, v3;
	Vector3 n1, n2, n3;
	Vector2 uv1, uv2, uv3;

	Triangle();
	Triangle(Vector3 v1, Vector3 v2, Vector3 v3);
	Triangle(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 n1, Vector3 n2, Vector3 n3);
	Triangle(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 n1, Vector3 n2, Vector3 n3, Vector2 uv1, Vector2 uv2, Vector2 uv3);

	Intersection* GetIntersection(Ray& ray, bool backsidedClipping = true) override;
};

