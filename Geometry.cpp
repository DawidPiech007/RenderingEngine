#include "Geometry.h"

Geometry::Geometry()
{
	material = new Material("default");
}

Geometry::Geometry(Material& material)
{
	this->material = &material;
}

Intersection* Geometry::GetIntersection(Ray& ray, bool backsidedClipping)
{
	return nullptr;
}
