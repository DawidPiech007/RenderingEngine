#define _CRT_SECURE_NO_WARNINGS

#include "Mesh.h"
#include "Renderer.h"
#include "ICamera.h"
#include "Ray.h"

using namespace std;

Mesh::Mesh()
{
	triangles = vector<Triangle>();
}

Intersection* Mesh::GetIntersection(Ray& ray, bool backsidedClipping)
{
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
