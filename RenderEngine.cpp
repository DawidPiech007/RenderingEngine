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
    stbi_set_flip_vertically_on_load(true);
    Texture* texture = new Texture("UV.png", SPHERICAL);

    camera->SetFOV(80);
    camera->position = Vector3(.0f, .0f,  -9.5f);
    CameraOrthographic* orthographic = new CameraOrthographic();
    RENDERER.SetUp(*buffer, *camera, 0.49); // 1/2 - 0.01 czyli rekurencja pójdzie 3 razy w dół

    // ========== DROW SCENE ==========
    vector<Geometry*> objects{};
    ParserOBJ::AddNewObjectsToVectorFromOBJ("monkey.obj", objects);
    
    objects[0]->material->texture = texture;

    Material* redMaterial = new Material("redMaterial", texture);
    objects[0]->material = redMaterial;
    redMaterial->ambient = LightIntensity(0.2f, 0.2f, 0.2f);
    redMaterial->diffuse = LightIntensity(0.7f, 0.7f, 0.7f);
    redMaterial->specular = LightIntensity(1.0f, 1.0f, 1.0f);
    redMaterial->shinines = 8.0f;
    Sphere* sph = new Sphere(Vector3(1.2f, -1.6f, -3.0f), 1.0f, redMaterial);
    objects.push_back(sph);
    //std::cout << sph.center.ToString();
    //objects.push_back(new Sphere(Vector3(3.0f, -5.0f, 6.0f), 3.0f, redMaterial));

    vector<Light*> lights{ //new PointLight(LightIntensity(1.0f,1.0f,1.0f), Vector3(6.0f, 0.0f, -15.0f), 1.0f, 0.045f, 0.0075f),
                           new PointLight(LightIntensity(1.0f,1.0f,1.0f), Vector3(-2.0f, 0.0f, -8.0f), 1.0f, 0.045f, 0.0075f),
                           new AmbientLight(LightIntensity(0.5f, 0.5f, 0.5f))};

    buffer->FillColor(0.0f, 0.0f, 0.0f);
    RENDERER.Render(objects, lights);
    //RENDERER.RenderNoAntiAliasing(objects, lights);


    // ========== DROW LIGHTS ==========
    vector<Light*> fakeLights{ new AmbientLight(LightIntensity(1.0f, 1.0f, 1.0f)) }; //TODO DELETE POINTERS
    Material* lightMaterial = new Material("lightMaterial",texture);
    lightMaterial->ambient = LightIntensity(1.0f, 1.0f, 1.0f);
    //vector<Geometry*> lightsObjects{ new Sphere(Vector3(-1.0f, 0.0f, -10.0f), 0.2f, lightMaterial)
                                    //, new Sphere(Vector3(1.0f, 0.0f, -6.0f), 0.2f, lightMaterial) 
     //                               };
    //RENDERER.Render(lightsObjects, fakeLights);
    //RENDERER.RenderNoAntiAliasing(lightsObjects, fakeLights);

    // ========== SAVE FILE ==========
    int comp = 3;
    char const* filename = "testPerspective.png";
    stbi_write_png(filename, buffer->width, buffer->height, comp, buffer->data, 0);

    delete camera, orthographic, buffer, RENDERER , lightMaterial, texture, redMaterial;

    for (Geometry* g : objects)
    {
        delete g;
    }
    objects.clear();

    return 0;
}
