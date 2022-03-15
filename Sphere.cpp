#include "Sphere.hpp"
#include "Vector3.hpp"
#include "Ray.hpp"

using namespace std;

Sphere::Sphere(float cx, float cy, float cz, float r)
{
	this->center = Vector3(cx, cy, cz);
	this->radius = r;
}

Sphere::Sphere(Vector3 c, float r)
{
	this->center = c;
	this->radius = r;
}

Sphere::Sphere()
{
	this->center = Vector3();
	this->radius = 0;
}

vector<Vector3*> Sphere::IntersectPoints(Ray& ray)
{
	vector<Vector3*> contactPoints; // lista puktow przeciecia (zwracana na koncu)

	Vector3 offset = ray.origin - center;
	Vector3 d2 = ray.direction * 2.0f;
	float a = Vector3::Dot(ray.direction, ray.direction);
	float b = Vector3::Dot(d2, offset);
	float c = Vector3::Dot(offset, offset) - (radius * radius);
	float det = (b * b) - 4 * (a * c);

	if ( fabs(det) < FLT_EPSILON) // "det == 0" // delta = 0 oznacza 1 przeciecie
	{
		float t = (-b) / (2 * a);
		if (t >= 0) // Czy punkt przeciecia jest po wlasciwej stronie polprostej
			contactPoints.push_back(new Vector3(ray.RayStep(t)));
	}
	else if(det > 0) // dodatnia delta oznacza 2 przeciecia
	{
		det = sqrtf(det);
		float t1 = (-b - det) / (2 * a);
		float t2 = (-b + det) / (2 * a);
		if (t1 >= 0)// Czy punkt przeciecia jest po wlasciwej stronie polprostej
			contactPoints.push_back(new Vector3(ray.RayStep(t1)));
		if (t2 >= 0)// Czy punkt przeciecia jest po wlasciwej stronie polprostej
			contactPoints.push_back(new Vector3(ray.RayStep(t2)));
	}

	return contactPoints;
}

EIntersectType Sphere::Intersect(Ray& ray)
{
	Vector3 offset = ray.origin - center;
	Vector3 d2 = ray.direction * 2.0f;
	float a = Vector3::Dot(ray.direction, ray.direction);
	float b = Vector3::Dot(d2, offset);
	float c = Vector3::Dot(offset, offset) - (radius * radius);
	float det = (b * b) - 4 * (a * c);

	if (fabs(det) < FLT_EPSILON) // "det == 0" // delta = 0 oznacza 1 przeciecie
	{
		float t = (-b) / (2 * a);
		if (t >= 0) // Czy punkt przeciecia jest po wlasciwej stronie polprostej
			return ONE;
	}
	else if (det > 0) // dodatnia delta oznacza 2 przeciecia
	{
		det = sqrtf(det);
		float t1 = (-b - det) / (2 * a);
		float t2 = (-b + det) / (2 * a);
		if (t1 >= 0)// Czy punkt przeciecia jest po wlasciwej stronie polprostej
		{
			if (t2 >= 0)// Czy punkt przeciecia jest po wlasciwej stronie polprostej
			{
				return TWO;
			}
			return ONE;
		}
		else if (t2 >= 0)// Czy punkt przeciecia jest po wlasciwej stronie polprostej
		{
			return ONE;
		}
	}

	return NONE;
}
