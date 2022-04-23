#define _CRT_SECURE_NO_WARNINGS

#include "ParserOBJ.h"
#include <iostream>
#include "Material.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Triangle.h"
#include "Mesh.h"

using namespace std;

void ParserOBJ::AddNewObjectsToVectorFromOBJ(std::string path, std::vector<Geometry*> &objects)
{
	vector<Material*> materials{};
	vector<Mesh*> meshs{};
	int meshID = -1;
	
	FILE* file = fopen(path.c_str(), "r");
	if (file == NULL) {
		cout << "Impossible to open the file (.obj)\n";
		return;
	}
	
	vector<LightIntensity> tmpColors = { {1.f,0.f,0.f }, {0.f,1.f,0.f }, {0.f,0.f,1.f },
										 {1.f,1.f,0.f }, {0.f,1.f,1.f }, {1.f,0.f,1.f },
										 {1.f,1.f,1.f } };
	
	std::vector< Vector3 > temp_positions{};
	std::vector< Vector2 > temp_uv{};
	std::vector< Vector3 > temp_normals{};
	
	while (1) {
	
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
	
		// else : parse lineHeader
	
		if (strcmp(lineHeader, "o") == 0) { // New Object
			meshID++;
			meshs.push_back(new Mesh());
		}
		else if (strcmp(lineHeader, "usemtl") == 0) {
			char materialName[128];
			fscanf(file, "%s", materialName);
			bool find = false;
			for (int i = 0; i < materials.size(); i++)
			{
				if (materialName == materials[i]->name)
				{
					find = true;
					meshs[meshID]->material = materials[i];
					break;
				}
			}
			if (find == false)
			{
				printf("File can't be read (wrong material name)\n");
				fclose(file);
				return;
			}
		}
		else if (strcmp(lineHeader, "mtllib") == 0) {
			char mtlFile[128];
			fscanf(file, "%s", mtlFile);
			AddNewMaterialToVectorFromMTL(mtlFile, materials);
		}
		else if (strcmp(lineHeader, "v") == 0) {
			Vector3 pos{};
			fscanf(file, "%f %f %f\n", &pos.x, &pos.y, &pos.z);
			temp_positions.push_back(pos);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			Vector2 uv{};
			fscanf(file, "%f %f\n", &uv.u, &uv.v);
			temp_uv.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			Vector3 normal{};
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			unsigned int posIndex[4];
			unsigned int normalIndex[4];
			unsigned int uvIndex[4];

			int matches = 0;

			if (temp_uv.size() > 0)
			{
				matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n",
					&posIndex[0], &uvIndex[0], &normalIndex[0], &posIndex[1], &uvIndex[1], &normalIndex[1],
					&posIndex[2], &uvIndex[2], &normalIndex[2], &posIndex[3], &uvIndex[3], &normalIndex[3]);

				if (matches == 9) // siatka z trójk¹tów, zawiera uv
				{
					LightIntensity tmpColor = tmpColors[meshs[meshID]->triangles.size() % tmpColors.size()];
					meshs[meshID]->triangles.push_back(Triangle(
						temp_positions[posIndex[0] - 1], temp_positions[posIndex[1] - 1], temp_positions[posIndex[2] - 1],
						temp_normals[normalIndex[0] - 1], temp_normals[normalIndex[1] - 1], temp_normals[normalIndex[2] - 1],
						temp_uv[uvIndex[0] - 1], temp_uv[uvIndex[1] - 1], temp_uv[uvIndex[2] - 1], tmpColor));
				}
				else if (matches == 12)// siatka z czworok¹tów, zawiera uv
				{
					LightIntensity tmpColor = tmpColors[meshs[meshID]->triangles.size() % tmpColors.size()];
					meshs[meshID]->triangles.push_back(Triangle(
						temp_positions[posIndex[0] - 1], temp_positions[posIndex[1] - 1], temp_positions[posIndex[2] - 1],
						temp_normals[normalIndex[0] - 1], temp_normals[normalIndex[1] - 1], temp_normals[normalIndex[2] - 1],
						temp_uv[uvIndex[0] - 1], temp_uv[uvIndex[1] - 1], temp_uv[uvIndex[2] - 1], tmpColor));
					meshs[meshID]->triangles.push_back(Triangle(
						temp_positions[posIndex[3] - 1], temp_positions[posIndex[1] - 1], temp_positions[posIndex[2] - 1],
						temp_normals[normalIndex[3] - 1], temp_normals[normalIndex[1] - 1], temp_normals[normalIndex[2] - 1],
						temp_uv[uvIndex[3] - 1], temp_uv[uvIndex[1] - 1], temp_uv[uvIndex[2] - 1], tmpColor));
				}
				else // B³êdna siatka lub siatka bez Normalnych
				{
					printf("File can't be read\n");
					fclose(file);
					return;
				}
			}
			else
			{
				matches = fscanf(file, "%d//%d %d//%d %d//%d %d//%d\n",
					&posIndex[0], &normalIndex[0], &posIndex[1], &normalIndex[1],
					&posIndex[2], &normalIndex[2], &posIndex[3], &normalIndex[3]);
				if (matches == 8)// siatka z czworok¹tów, NIE zawiera uv
				{
					LightIntensity tmpColor = tmpColors[meshs[meshID]->triangles.size() % tmpColors.size()];

					meshs[meshID]->triangles.push_back(Triangle(
						temp_positions[posIndex[0] - 1], temp_positions[posIndex[1] - 1], temp_positions[posIndex[2] - 1],
						temp_normals[normalIndex[0] - 1], temp_normals[normalIndex[1] - 1], temp_normals[normalIndex[2] - 1], tmpColor));
					meshs[meshID]->triangles.push_back(Triangle(
						temp_positions[posIndex[3] - 1], temp_positions[posIndex[1] - 1], temp_positions[posIndex[2] - 1],
						temp_normals[normalIndex[3] - 1], temp_normals[normalIndex[1] - 1], temp_normals[normalIndex[2] - 1], tmpColor));
				}
				else if (matches == 6)// siatka z trójk¹tów, NIE zawiera uv
				{
					LightIntensity tmpColor = tmpColors[meshs[meshID]->triangles.size() % tmpColors.size()];

					meshs[meshID]->triangles.push_back(Triangle(
						temp_positions[posIndex[0] - 1], temp_positions[posIndex[1] - 1], temp_positions[posIndex[2] - 1],
						temp_normals[normalIndex[0] - 1], temp_normals[normalIndex[1] - 1], temp_normals[normalIndex[2] - 1], tmpColor));
				}
				else // B³êdna siatka lub siatka bez Normalnych
				{
					printf("File can't be read\n");
					fclose(file);
					return;
				}
			}

			//cout << "\nmatches = " << matches << endl;
			//for (int i = 0; i < 4; i++)
			//	cout << "posIndex[" << i << "] = " << posIndex[i] << endl;
			//for (int i = 0; i < 4; i++)
			//	cout << "uvIndex[" << i << "] = " << uvIndex[i] << endl;
			//for (int i = 0; i < 4; i++)
			//	cout << "normalIndex[" << i << "] = " << normalIndex[i] << endl;
			
		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	
	}
	

	for (int i = 0; i < meshs.size(); i++)
	{
		objects.push_back(meshs[i]);
	}
}

void ParserOBJ::AddNewMaterialToVectorFromMTL(std::string path, std::vector<Material*> &materials)
{
	FILE* file = fopen(path.c_str(), "r");
	if (file == NULL) {
		cout << "Impossible to open the file (.mlt)\n";
		return;
	}

	int materialID = materials.size() - 1;

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader

		if (strcmp(lineHeader, "newmtl") == 0) { // New Material
			char materialName[128];
			fscanf(file, "%s", materialName);
			materialID++;
			materials.push_back(new Material(materialName));
		}
		else if (strcmp(lineHeader, "Ns") == 0) {
			float shinines;
			fscanf(file, "%f\n", &shinines);
			materials[materialID]->SetValue(shinines, "Ns");
		}
		else if (strcmp(lineHeader, "Ka") == 0) {
			LightIntensity ambient{};
			fscanf(file, "%f %f %f\n", &ambient.r, &ambient.g, &ambient.b);
			materials[materialID]->SetValue(ambient, "Ka");
		}
		else if (strcmp(lineHeader, "Kd") == 0) {
			LightIntensity diffuse{};
			fscanf(file, "%f %f %f\n", &diffuse.r, &diffuse.g, &diffuse.b);
			materials[materialID]->SetValue(diffuse, "Kd");
		}
		else if (strcmp(lineHeader, "Ks") == 0) {
			LightIntensity specular{};
			fscanf(file, "%f %f %f\n", &specular.r, &specular.g, &specular.b);
			materials[materialID]->SetValue(specular, "Ks");
		}
		else if (strcmp(lineHeader, "d") == 0) {
			float transparency;
			fscanf(file, "%f\n", &transparency);
			materials[materialID]->SetValue(transparency, "d");
		}
	}
}
