#include "Triangle.h"
#include "Ray.h"
#include <iostream>

Triangle::Triangle(): v1(Vector3::Zero()), v2(Vector3::Zero()), v3(Vector3::Zero()) {}


Triangle::Triangle(Vector3 v1, Vector3 v2, Vector3 v3): v1(v1), v2(v2), v3(v3), Geometry() {}

Triangle::Triangle(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 n1, Vector3 n2, Vector3 n3)
{
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	this->n1 = n1.Normalize();
	this->n2 = n2.Normalize();
	this->n3 = n3.Normalize();
}

Triangle::Triangle(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 n1, Vector3 n2, Vector3 n3, Vector2 uv1, Vector2 uv2, Vector2 uv3)
{
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	this->n1 = n1.Normalize();
	this->n2 = n2.Normalize();
	this->n3 = n3.Normalize();
	this->uv1 = uv1;
	this->uv2 = uv2;
	this->uv3 = uv3;
}

Intersection* Triangle::GetIntersection(Ray& ray, bool backsidedClipping)
{
	// Wyznaczanie Normalnej trujk?ta
	Vector3 v1v2 = v2 - v1;
	Vector3 v1v3 = v3 - v1;
	Vector3 normal = Vector3::Cross(v1v2, v1v3);
	normal = normal.Normalize();

	Vector3 crossProd = Vector3::Cross(v1v2, v1v3);
	float field = Vector3::Dot(crossProd, normal);

	float dir = Vector3::Dot(normal, ray.direction);

	if(backsidedClipping)
		if (dir > EPSILON) //backsided
			return nullptr;

	if (fabs(dir) < EPSILON)
		return nullptr; //paralell, no intersection

	float d = Vector3::Dot(-normal, v1);
	float t = -(Vector3::Dot(normal, ray.origin) + d) / dir;

	if (t < 0)
		return nullptr; // ray behind the triangle

	Vector3 point = ray.RayStep(t);

	//v1
	Vector3 e1 = v2 - v1;
	Vector3 vp1 = point - v1;
	Vector3 c1 = Vector3::Cross(e1, vp1);
	float fieldv1 = Vector3::Dot(c1, normal);

	float alpha = fieldv1 / field;
	if (alpha >= 1 || alpha <= 0)
		return nullptr;

	Vector3 e2 = v3 - v2;
	Vector3 vp2 = point - v2;
	Vector3 c2 = Vector3::Cross(e2, vp2);
	float fieldv2 = Vector3::Dot(c2, normal);

	float beta = fieldv2 / field;
	if (beta >= 1 || beta <= 0)
		return nullptr;

	//v3
	Vector3 e3 = v1 - v3;
	Vector3 vp3 = point - v3;
	Vector3 c3 = Vector3::Cross(e3, vp3);
	float fieldv3 = Vector3::Dot(c3, normal);

	float theta = fieldv3 / field;
	if (theta >= 1 || theta <= 0)
		return nullptr;

	return new Intersection(Vector3(ray.RayStep(t)), n1 * alpha + n2 * beta + n3 * theta);
}

