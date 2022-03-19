#include "Geometry.hpp"

Geometry::Geometry() : baseColor(1.0f,1.0f,1.0f)
{
}

Geometry::Geometry(LightIntensity baseColor)
{
	this->baseColor = baseColor;
}

std::vector<Vector3*> Geometry::IntersectPoints(Ray& ray)
{
	return std::vector<Vector3*>();
}

EIntersectType Geometry::Intersect(Ray& ray)
{
	return NONE;
}
