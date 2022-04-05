#include "Mesh.hpp"

Mesh::Mesh(std::string path, LightIntensity baseColor)
{
	this->baseColor = baseColor;
	//TODO load object from obj
}

Vector3* Mesh::IntersectPoint(Ray& ray)
{
	// TODO IntersectPoint() for all triangles
	// TODO find closest point to camera
	return nullptr;
}
