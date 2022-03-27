#include <iostream>

#include "Vector3.hpp"
#include "Ray.hpp"
#include "LightIntensity.hpp"

#include "Geometry.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"

#include "Buffer.hpp"
#include "Camera.hpp"
#include "CameraOrthographic.hpp"
#include "Renderer.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;

int main()
{
    Buffer* buffer = new Buffer(3840, 2160);
    Camera* camera = new Camera();
    camera->SetFOV(60);
    CameraOrthographic* orthographic = new CameraOrthographic();
    RENDERER.SetUp(*buffer, *camera, 0.126); // 1/8 + 0.001 czyli rekurencja pójdzie 4 razy w dół

    buffer->MakeColoredBackGround();
    //buffer->FillColor(0.0f,0.0f,0.0f);

    vector<Geometry*> objects{  new Sphere(0.0f, 0.0f, 1.0f, 0.3f, LightIntensity(1.0f,0.0f,0.0f)),
                                new Sphere(-0.8f, 0.4f, 2.0f, 0.3f, LightIntensity(1.0f,1.0f,0.0f)), 
                                new Sphere(0.99f, 0.0f, 2.0f, 0.3f, LightIntensity(1.0f,0.0f,1.0f)), };

    RENDERER.RenderAdaptive(objects);

    int comp = 3;
    char const* filename = "testPerspective.png";
    stbi_write_png(filename, buffer->width, buffer->height, comp, buffer->data, 0);


    buffer->MakeColoredBackGround();
    //buffer->FillColor(0.0f, 0.0f, 0.0f);
    RENDERER.SetCamera(*orthographic);
    RENDERER.RenderAdaptive(objects);

    filename = "testOrtographic.png";
    stbi_write_png(filename, buffer->width, buffer->height, comp, buffer->data, 0);



    delete camera, orthographic, buffer, RENDERER;
    objects.clear();

    return 0;
}
