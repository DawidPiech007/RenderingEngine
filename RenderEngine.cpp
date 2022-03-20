﻿#include <iostream>

#include "Vector3.hpp"
#include "Ray.hpp"
#include "LightIntensity.hpp"

#include "Geometry.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"

#include "Buffer.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;

int main()
{
    Buffer* buffer = new Buffer(600, 600);
    Camera* camera = new Camera();
    Renderer* renderer = new Renderer(*buffer, *camera);

    //buffer->FillColor(0, 0, 0);
    buffer->MakeColoredBackGround();

    vector<Geometry*> objects{  new Sphere(0.0f, 0.0f, 1.0f, 0.5f, LightIntensity(1.0f,0.0f,0.0f)),
                                new Sphere(-1.0f, 0.3f, 2.0f, 0.5f, LightIntensity(1.0f,1.0f,0.0f)), 
                                new Sphere(1.0f, 0.0f, 10.0f, 1.5f, LightIntensity(1.0f,0.0f,1.0f)), };

    renderer->Render(objects);

    int comp = 3;
    char const* filename = "testPerspective.png";
    stbi_write_png(filename, buffer->width, buffer->height, comp, buffer->data, 0);


    buffer->MakeColoredBackGround();
    renderer->BasicRender(objects);

    filename = "testOrtographic.png";
    stbi_write_png(filename, buffer->width, buffer->height, comp, buffer->data, 0);

    delete camera, buffer, renderer;
    objects.clear();

    return 0;
}
