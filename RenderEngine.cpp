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

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;

int main()
{
    Buffer* buffer = new Buffer(400, 400);
    Camera* camera = new Camera();
    camera->SetFOV(60);
    camera->position = Vector3(.5f, .5f,  -25.0f);
    CameraOrthographic* orthographic = new CameraOrthographic();
    RENDERER.SetUp(*buffer, *camera, 0.49); // 1/2 - 0.001 czyli rekurencja pójdzie 3 razy w dół


    Vector3 v1(-1, -1, 5);
    Vector3 v2(1, -1, 5);
    Vector3 v3(0, 1, 5);

    Triangle t(v1, v2, v3, LightIntensity(0.8f, 0.4f, 0.2f));
    Mesh mesh("monkey_in_box_simple.obj", LightIntensity(1.0f, 0.0f, 0.0f));


    //vector<Geometry*> objects{ new Sphere(0.0f, 0.0f, 9.0f, 0.3f, LightIntensity(1.0f, 0.0f, 0.0f)),
    //                            new Sphere(-0.1f, 0.0f, 9.0f, 0.3f, LightIntensity(1.0f, 1.0f, 0.0f)),
    //                            new Sphere(0.2f, 0.0f, 9.0f, 0.3f, LightIntensity(1.0f, 0.0f, 1.0f)),
    //                            &t };

    vector<Geometry*> objects{ &mesh };

    //ParserOBJ::AddNewObjectsToVector("testObjct2.obj", objects);

    //buffer->MakeColoredBackGround();
    buffer->FillColor(0.0f, 0.0f, 0.0f);
    RENDERER.Render(objects);

    int comp = 3;
    char const* filename = "testPerspective.png";
    stbi_write_png(filename, buffer->width, buffer->height, comp, buffer->data, 0);


    //buffer->MakeColoredBackGround();
    //buffer->FillColor(0.0f, 0.0f, 0.0f);
    //RENDERER.SetCamera(*orthographic);
    //RENDERER.Render(objects);
    //
    //filename = "testOrtographic.png";
    //stbi_write_png(filename, buffer->width, buffer->height, comp, buffer->data, 0);



    delete camera, orthographic, buffer, RENDERER;
    objects.clear();


    return 0;
}
