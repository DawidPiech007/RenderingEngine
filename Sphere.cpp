#include "Sphere.h"
#include "Vector3.h"
#include "Ray.h"

using namespace std;

Sphere::Sphere(float cx, float cy, float cz, float r) : Geometry()
{
	this->center = Vector3(cx, cy, cz);
	this->radius = r;
}

Sphere::Sphere(Vector3 c, float r) : Geometry()
{
	this->center = c;
	this->radius = r;
}

Sphere::Sphere() : Geometry()
{
	this->center = Vector3();
	this->radius = 0;
}

Intersection* Sphere::GetIntersection(Ray& ray, bool backsidedClipping)
{
	Vector3 offset = ray.origin - center;

	// je�li promie� zaczyna si� w sferze to nie zwracamy przeci�� przy w��czonym backsidedClippingu
	if (backsidedClipping)
		if (offset.SqrMagnitude() < (radius * radius))
			return nullptr;

	Vector3 d2 = ray.direction * 2.0f;
	float a = Vector3::Dot(ray.direction, ray.direction);
	float b = Vector3::Dot(d2, offset);
	float c = Vector3::Dot(offset, offset) - (radius * radius);
	float det = (b * b) - 4 * (a * c);

	if (fabs(det) < FLT_EPSILON) // "det == 0" // delta = 0 oznacza 1 przeciecie
	{
		float t = (-b) / (2 * a);
		if (t >= 0) // Czy punkt przeciecia jest po wlasciwej stronie polprostej
		{
			Vector3 point = Vector3(ray.RayStep(t));
			Vector3 normal = point - center;
			return new Intersection(point, normal);
		}
	}
	else if (det > 0) // dodatnia delta oznacza 2 przeciecia
	{
		det = sqrtf(det);
		float t1 = (-b - det) / (2 * a);
		float t2 = (-b + det) / (2 * a);
		if (t1 >= 0)// Czy punkt przeciecia jest po wlasciwej stronie polprostej
			if (t1 < t2) // czy t1 jest bli�ej
			{
				Vector3 point = Vector3(ray.RayStep(t1));
				Vector3 normal = point - center;
				return new Intersection(point, normal);
			}
		if (t2 >= 0)// Czy punkt przeciecia jest po wlasciwej stronie polprostej
			if (t2 < t1) // czy t2 jest bli�ej
			{
				Vector3 point = Vector3(ray.RayStep(t2));
				Vector3 normal = point - center;
				return new Intersection(point, normal);
			}
	}

	return nullptr;
}
