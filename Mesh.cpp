#define _CRT_SECURE_NO_WARNINGS

#include "Mesh.hpp"
#include "Renderer.hpp"
#include "ICamera.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>

using namespace std;

Mesh::Mesh(string path, LightIntensity baseColor)
{
	this->baseColor = baseColor;

	FILE* file = fopen(path.c_str(), "r");
	if (file == NULL) {
		cout<<"Impossible to open the file\n";
		return;
	}

	vector<LightIntensity> tmpColors = { {1.f,0.f,0.f }, {0.f,1.f,0.f }, {0.f,0.f,1.f },
										 {1.f,1.f,0.f }, {0.f,1.f,1.f }, {1.f,0.f,1.f },
										 {1.f,1.f,1.f }};
	
	std::vector< Vector3 > temp_positions{};
	//std::vector< Vector3 > temp_uvs;
	std::vector< Vector3 > temp_normals{};

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0) {
			Vector3 pos{};
			fscanf(file, "%f %f %f\n", &pos.x, &pos.y, &pos.z);
			temp_positions.push_back(pos);
		}
		//else if (strcmp(lineHeader, "vt") == 0) {
		//	Vector2 uv{};
		//	fscanf(file, "%f %f\n", uv.x, uv.y);
		//	temp_uvs.push_back(uv);
		//}
		else if (strcmp(lineHeader, "vn") == 0) {
			Vector3 normal{};
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			//unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			unsigned int posIndex[3], normalIndex[3];
			//int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &posIndex[0], &normalIndex[0], &posIndex[1], &normalIndex[1], &posIndex[2], &normalIndex[2]);
			if (matches != 6) {
				printf("File can't be read\n");
				fclose(file);
				return;
			}

			LightIntensity tmpColor = tmpColors[triangles.size() % tmpColors.size()];

			triangles.push_back(Triangle(
				Vector3(temp_positions[posIndex[0]-1].x, temp_positions[posIndex[0]-1].y, temp_positions[posIndex[0]-1].z),
				Vector3(temp_positions[posIndex[1]-1].x, temp_positions[posIndex[1]-1].y, temp_positions[posIndex[1]-1].z),
				Vector3(temp_positions[posIndex[2]-1].x, temp_positions[posIndex[2]-1].y, temp_positions[posIndex[2]-1].z),
				tmpColor));
		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	//for (int i = 0; i < temp_positions.size(); i++)
	//{
	//	cout << "pos[" << i << "].Magnitude() = " << temp_positions[i].Magnitude() << "\n";
	//	cout << "pos[" << i << "].x = " << temp_positions[i].x << "\n";
	//	cout << "pos[" << i << "].y = " << temp_positions[i].y << "\n";
	//	cout << "pos[" << i << "].z = " << temp_positions[i].z << "\n";
	//}
	//
	//for (int i = 0; i < triangles.size(); i++)
	//{
	//	cout << "triangles[" << i << "].v1.Magnitude() = " << triangles[i].v1.Magnitude() << "\n";
	//	cout << "triangles[" << i << "].v2.Magnitude() = " << triangles[i].v2.Magnitude() << "\n";
	//	cout << "triangles[" << i << "].v3.Magnitude() = " << triangles[i].v3.Magnitude() << "\n";
	//}

}

Vector3* Mesh::IntersectPoint(Ray& ray)
{
	Vector3* retVector3 = nullptr;
	vector<Vector3*> intersectPoints;
	for (int k = 0; k < triangles.size(); k++)
	{
		intersectPoints.push_back(triangles[k].IntersectPoint(ray));
	}

	// find object clostes to camera
	float distanceMin = std::numeric_limits<float>::max();
	int indexMin = -1;
	for (int k = 0; k < triangles.size(); k++)
	{
		if (intersectPoints[k] != nullptr)
		{
			float distance = (RENDERER.GetCanera()->GetPosition() - *intersectPoints[k]).SqrMagnitude();
			if (distance < distanceMin)
			{
				distanceMin = distance;
				indexMin = k;

				delete retVector3;
				retVector3 = new Vector3(intersectPoints[k]->x, intersectPoints[k]->y, intersectPoints[k]->z);
			}
			delete intersectPoints[k]; // delate pointer
		}
	}
	intersectPoints.clear();

	tmpLastUsedTriangleIndex = indexMin;

	return retVector3;
}

LightIntensity Mesh::GetColor()
{
	//return baseColor;

	if (tmpLastUsedTriangleIndex == -1)
	{
		return LightIntensity();
	}

	return triangles[tmpLastUsedTriangleIndex].GetColor();
}
