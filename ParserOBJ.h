#pragma once

#include <vector>
#include <string>

class Geometry;

class ParserOBJ
{
public:
	static void AddNewObjectsToVector(std::string path, std::vector<Geometry*> objects);
};

