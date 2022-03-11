#include "Sphere.hpp"
#include "Vector3.hpp"
#include "Ray.hpp"

using namespace std;

Sphere::Sphere(Vector3& c, float r): r(r)
{
	this->c = new Vector3(c.x, c.y, c.z);
}

Sphere::Sphere()
{
	this->c = new Vector3();
	r = 0;
}

list<Vector3*> Sphere::Intersect(Ray& ray)
{
	list<Vector3*> contactPoints; // lista puktow przeciecia (zwracana na koncu)

	Vector3 offset = ray.origin - *c;
	Vector3 d2 = ray.direction * 2.0f;
	float a = Vector3::Dot(ray.direction, ray.direction);
	float b = Vector3::Dot(d2, offset);
	float c = Vector3::Dot(offset, offset) - (r * r);
	float det = (b * b) - 4 * (a + c);

	if ( fabs(det) > FLT_EPSILON) // "det == 0" // delta = 0 oznacza 1 przeciecie
	{
		float t = (-b) / (2 * a);
		if (t >= 0 && t <= 1) // Czy punkt przeciecia jest pomiendzy poczatkiem a koncem promienia
			contactPoints.push_back(new Vector3(ray.RayStep(t)));
	}
	else if(det > 0) // dodatnia delta oznacza 2 przeciecia
	{
		det = sqrtf(det);
		float t1 = (-b - det) / (2 * a);
		float t2 = (-b + det) / (2 * a);
		if (t1 >= 0 && t1 <= 1)// Czy punkt przeciecia jest pomiendzy poczatkiem a koncem promienia
			contactPoints.push_back(new Vector3(ray.RayStep(t1)));
		if (t2 >= 0 && t2 <= 1)// Czy punkt przeciecia jest pomiendzy poczatkiem a koncem promienia
			contactPoints.push_back(new Vector3(ray.RayStep(t2)));
	}

	return contactPoints;
}

/*
int Sphere::Intersect( Ray& a_Ray, float& a_Dist )
{
	vector3 v = a_Ray.GetOrigin() - m_Centre;
	float b = -DOT( v, a_Ray.GetDirection() );
	float det = (b * b) - DOT( v, v ) + m_SqRadius;
	int retval = MISS;
	if (det > 0)
	{
		det = sqrtf( det );
		float i1 = b - det;
		float i2 = b + det;
		if (i2 > 0)
		{
			if (i1 < 0)
			{
				if (i2 < a_Dist)
				{
					a_Dist = i2;
					retval = INPRIM;
				}
			}
			else
			{
				if (i1 < a_Dist)
				{
					a_Dist = i1;
					retval = HIT;
				}
			}
		}
	}
	return retval;
}
*/
