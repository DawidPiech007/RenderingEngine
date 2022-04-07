#include "Geometry.hpp"
#include "Vector3.hpp"

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

Vector3* Geometry::IntersectPoint(Ray& ray)
{
	return nullptr;
}

EIntersectType Geometry::Intersect(Ray& ray)
{
	return NONE;
}

LightIntensity Geometry::GetColor()
{
	return baseColor;
}
