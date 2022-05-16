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
#include "Texture.h"
#include "Camera.h"
#include "CameraOrthographic.h"
#include "Renderer.h"
#include "ParserOBJ.h"

#include "PointLight.h"
#include "AmbientLight.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image_write.h"
#include "stb_image.h"

using namespace std;

int main()
{
    // ========== SETUP ==========
    Buffer* buffer = new Buffer(400, 400);
    Camera* camera = new Camera();
    Texture* texture = new Texture("texture.png");
    std::cout << texture->GetColor(0, 200).r << "\n";
    camera->SetFOV(80);
    camera->position = Vector3(.0f, .0f,  -2.5f);
    CameraOrthographic* orthographic = new CameraOrthographic();
    RENDERER.SetUp(*buffer, *camera, 0.49); // 1/2 - 0.01 czyli rekurencja pójdzie 3 razy w dół

    // ========== DROW SCENE ==========
    vector<Geometry*> objects{};
    //ParserOBJ::AddNewObjectsToVectorFromOBJ("monkey_in_box.obj", objects);

    Material* redMaterial = new Material("redMaterial", texture);
    redMaterial->ambient = LightIntensity(1.0f, 0.0f, 0.0f);
    redMaterial->diffuse = LightIntensity(1.0f, 0.0f, 0.0f);
    redMaterial->specular = LightIntensity(1.0f, 1.0f, 1.0f);
    redMaterial->shinines = 32.0f;
    objects.push_back(new Sphere(Vector3(0.0f, 0.0f, 0.0f), 1.0f, redMaterial));
    //objects.push_back(new Sphere(Vector3(3.0f, -5.0f, 6.0f), 3.0f, redMaterial));

    vector<Light*> lights{ new PointLight(LightIntensity(1.0f,1.0f,1.0f), Vector3(-1.0f, 0.0f, -10.0f), 1.0f, 0.045f, 0.0075f),
                           //new PointLight(LightIntensity(1.0f,1.0f,1.0f), Vector3(1.0f, 0.0f, -6.0f), 1.0f, 0.001f, 0.002f),
                           new AmbientLight(LightIntensity(0.05f, 0.05f, 0.1f))};

    buffer->FillColor(0.0f, 0.0f, 0.0f);
    RENDERER.Render(objects, lights);
    //RENDERER.RenderNoAntiAliasing(objects, lights);


    // ========== DROW LIGHTS ==========
    vector<Light*> fakeLights{ new AmbientLight(LightIntensity(1.0f, 1.0f, 1.0f)) };
    Material* lightMaterial = new Material("lightMaterial",texture);
    lightMaterial->ambient = LightIntensity(1.0f, 1.0f, 1.0f);
    vector<Geometry*> lightsObjects{ new Sphere(Vector3(-1.0f, 0.0f, -10.0f), 0.2f, lightMaterial)
                                    //, new Sphere(Vector3(1.0f, 0.0f, -6.0f), 0.2f, lightMaterial) 
                                    };
    //RENDERER.Render(lightsObjects, fakeLights);
    //RENDERER.RenderNoAntiAliasing(lightsObjects, fakeLights);

    // ========== SAVE FILE ==========
    int comp = 3;
    char const* filename = "testPerspective.png";
    stbi_write_png(filename, buffer->width, buffer->height, comp, buffer->data, 0);

    delete camera, orthographic, buffer, RENDERER , lightMaterial;
    objects.clear();

    delete buffer, camera;

    return 0;
}
