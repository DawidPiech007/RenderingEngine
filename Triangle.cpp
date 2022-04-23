#include "Triangle.h"
#include "Ray.h"
#include <iostream>

Triangle::Triangle(): v1(Vector3::Zero()), v2(Vector3::Zero()), v3(Vector3::Zero()) {}

Triangle::Triangle(Vector3 v1, Vector3 v2, Vector3 v3, LightIntensity baseColor): v1(v1), v2(v2), v3(v3), Geometry(baseColor) {}

Triangle::Triangle(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 n1, Vector3 n2, Vector3 n3, LightIntensity baseColor)
{
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	this->n1 = n1;
	this->n2 = n2;
	this->n3 = n3;
	this->baseColor = baseColor;
}

Triangle::Triangle(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 n1, Vector3 n2, Vector3 n3, Vector2 uv1, Vector2 uv2, Vector2 uv3, LightIntensity baseColor)
{
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	this->n1 = n1;
	this->n2 = n2;
	this->n3 = n3;
	this->uv1 = uv1;
	this->uv2 = uv2;
	this->uv3 = uv3;
	this->baseColor = baseColor;
}

std::vector<Vector3*> Triangle::IntersectPoints(Ray& ray)
{
	return std::vector<Vector3*>();
}

Vector3* Triangle::IntersectPoint(Ray& ray)
{
	Vector3 v1v2 = v2 - v1;
	Vector3 v1v3 = v3 - v1;

	Vector3 normal = Vector3::Cross(v1v2, v1v3);
	normal = normal.Normalize();
	float dir = Vector3::Dot(normal, ray.direction);

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

	if (Vector3::Dot(normal, c1) < EPSILON)
		return nullptr;

	Vector3 e2 = v3 - v2;
	Vector3 vp2 = point - v2;
	Vector3 c2 = Vector3::Cross(e2, vp2);

	if (Vector3::Dot(normal, c2) < EPSILON)
		return nullptr;

	//v3
	Vector3 e3 = v1 - v3;
	Vector3 vp3 = point - v3;
	Vector3 c3 = Vector3::Cross(e3, vp3);

	if (Vector3::Dot(normal, c3) < EPSILON)
		return nullptr;

	return new Vector3(ray.RayStep(t)); // TODO why &point doesnt work
}

EIntersectType Triangle::Intersect(Ray& ray)
{
	Vector3 v1v2 = v2 - v1;
	Vector3 v1v3 = v3 - v1;

	Vector3 normal = Vector3::Cross(v1v2, v1v3);

	float dir = Vector3::Dot(normal, ray.direction);

	if (fabs(dir) < 0.0001f) //epsilon
		return NONE; //paralell, no intersection

	float d = -Vector3::Dot(normal, v1);
	float t = -(Vector3::Dot(normal, ray.origin) + d) / dir;

	if (t < 0) 
		return NONE; // ray behind the triangle

	Vector3 point = ray.RayStep(t);

	//v1
	Vector3 e1 = v2 - v1;
	Vector3 vp1 = point - v1;
	Vector3 c1 = Vector3::Cross(e1, vp1);

	if (Vector3::Dot(normal, c1) < EPSILON)
		return NONE;

	Vector3 e2 = v3 - v2;
	Vector3 vp2 = point - v2;
	Vector3 c2 = Vector3::Cross(e2, vp2);

	if (Vector3::Dot(normal, c2) < EPSILON)
		return NONE;

	//v3
	Vector3 e3 = v1 - v3;
	Vector3 vp3 = point - v3;
	Vector3 c3 = Vector3::Cross(e3, vp3);

	if (Vector3::Dot(normal, c3) < EPSILON)
		return NONE;

	return ONE;
}
