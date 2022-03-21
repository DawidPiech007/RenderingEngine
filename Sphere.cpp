#include "Sphere.hpp"
#include "Vector3.hpp"
#include "Ray.hpp"

using namespace std;

Sphere::Sphere(float cx, float cy, float cz, float r, LightIntensity color) : Geometry(color)
{
	this->center = Vector3(cx, cy, cz);
	this->radius = r;
}

Sphere::Sphere(Vector3 c, float r, LightIntensity color) : Geometry(color)
{
	this->center = c;
	this->radius = r;
}

Sphere::Sphere() : Geometry()
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

Vector3* Sphere::IntersectPoint(Ray& ray)
{
	vector<Vector3*> contactPoints; // lista puktow przeciecia (zwracana na koncu)

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
			return new Vector3(ray.RayStep(t));
	}
	else if (det > 0) // dodatnia delta oznacza 2 przeciecia
	{
		det = sqrtf(det);
		float t1 = (-b - det) / (2 * a);
		float t2 = (-b + det) / (2 * a);
		if (t1 >= 0)// Czy punkt przeciecia jest po wlasciwej stronie polprostej
			if (t1 < t2 || t2 < 0)
				return new Vector3(ray.RayStep(t1));
		if (t2 >= 0)// Czy punkt przeciecia jest po wlasciwej stronie polprostej
			if (t2 < t1 || t1 < 0)
				return new Vector3(ray.RayStep(t2));
	}

	return nullptr;
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
