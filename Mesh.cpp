#define _CRT_SECURE_NO_WARNINGS

#include "Mesh.h"
#include "Renderer.h"
#include "ICamera.h"
#include "Ray.h"

using namespace std;

Mesh::Mesh()
{
	triangles = vector<Triangle>();
	Sphere boundingSphere;
}

void Mesh::SetUp()
{
	if (triangles.size() == 0)
		return;

	center = Vector3(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < triangles.size(); i++)
	{
		center += triangles[i].v1;
		center += triangles[i].v2;
		center += triangles[i].v3;
	}

	center *= 1 / triangles.size() * 3;
	float r = 0;

	for (int i = 0; i < triangles.size(); i++)
	{
		r = max((center, triangles[i].v1).Magnitude(), r);
		r = max((center, triangles[i].v2).Magnitude(), r);
		r = max((center, triangles[i].v3).Magnitude(), r);
	}
	boundingSphere = Sphere(center, r);
}

Intersection* Mesh::GetIntersection(Ray& ray, bool backsidedClipping)
{
	if (backsidedClipping == true) // false tylko dla promieni do œwiat³a
	{
		Intersection* sphereIntersection = boundingSphere.GetIntersection(ray, false);
		if (sphereIntersection == nullptr)
		{
			delete sphereIntersection;
			return nullptr;
		}
		delete sphereIntersection;
	}
	

	Intersection* retIntersection = nullptr;
	vector<Intersection*> intersections;
	for (int k = 0; k < triangles.size(); k++)
	{
		intersections.push_back(triangles[k].GetIntersection(ray, backsidedClipping));
	}

	// find object clostes to ray origin
	float distanceMin = std::numeric_limits<float>::max();
	int indexMin = -1;
	for (int k = 0; k < triangles.size(); k++)
	{
		if (intersections[k] != nullptr)
		{
			float distance = (ray.origin - intersections[k]->point).SqrMagnitude();
			if (distance < distanceMin)
			{
				distanceMin = distance;
				indexMin = k;

				delete retIntersection;
				retIntersection = new Intersection(intersections[k]->point, intersections[k]->normal);
			}
			delete intersections[k]; // delate pointer
		}
	}
	intersections.clear();

	tmpLastUsedTriangleIndex = indexMin;

	return retIntersection;
}
