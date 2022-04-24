//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#include "Vector3.h"
#include "Ray.h"
#include "LightIntensity.h"

#include "Geometry.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Mesh.h"

#include "Buffer.h"
#include "Camera.h"
#include "CameraOrthographic.h"
#include "Renderer.h"
#include "ParserOBJ.h"

#include "PointLight.h"
#include "AmbientLight.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;

int main()
{
    Buffer* buffer = new Buffer(400, 400);
    Camera* camera = new Camera();
    camera->SetFOV(80);
    camera->position = Vector3(.0f, .0f,  -9.5f);
    CameraOrthographic* orthographic = new CameraOrthographic();
    RENDERER.SetUp(*buffer, *camera, 0.49); // 1/2 - 0.001 czyli rekurencja pójdzie 3 razy w dół

    vector<Geometry*> objects{};
    //ParserOBJ::AddNewObjectsToVectorFromOBJ("monkey_in_box.obj", objects);
    ParserOBJ::AddNewObjectsToVectorFromOBJ("monkey_in_box.obj", objects);

    objects.push_back(new Sphere(Vector3(-2.0f, 2.0f, -4.0f), 0.3f));
    Material* material = new Material("name");
    material->SetValue(LightIntensity(1.0f, 0.0f, 0.0f), "Kd");
    material->SetValue(LightIntensity(1.0f, 0.0f, 0.0f), "Ka");
    objects[objects.size() - 1]->material = material;

    // Bez lub z małpą
    //objects[0] = objects[3];
    //objects.pop_back();

    vector<Light*> lights{ new PointLight(LightIntensity(1.0f,1.0f,1.0f), Vector3(-2.0f, 2.0f, -4.0f), 1.0f, 1.0f, 1.0f),
                           new AmbientLight(LightIntensity(0.05f, 0.05f, 0.1f))};

    //vector<Light*> lights{ new PointLight(LightIntensity(1.0f,1.0f,1.0f), Vector3(0.0f, 0.0f, 0.0f), 1.0f, 1.0f, 1.0f),
    //                       new AmbientLight(LightIntensity(0.05f, 0.05f, 0.1f)) };

    //buffer->MakeColoredBackGround();
    buffer->FillColor(0.0f, 0.0f, 0.0f);
    RENDERER.RenderNoAntiAliasing(objects, lights);

    int comp = 3;
    char const* filename = "testPerspective.png";
    stbi_write_png(filename, buffer->width, buffer->height, comp, buffer->data, 0);

    delete camera, orthographic, buffer, RENDERER;
    objects.clear();


    return 0;
}
