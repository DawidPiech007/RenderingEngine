#pragma once

#include <vector>
#include <string>

class Geometry;
class Material;

class ParserOBJ
{
public:
	static void AddNewObjectsToVectorFromOBJ(std::string path, std::vector<Geometry*> &objects);
	static void AddNewMaterialToVectorFromMTL(std::string path, std::vector<Material*> &materials);
};

