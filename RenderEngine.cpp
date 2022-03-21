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
    Buffer* buffer = new Buffer(600, 600);
    Camera* camera = new Camera();
    camera->SetFOV(60);
    CameraOrthographic* orthographic = new CameraOrthographic();
    Renderer* renderer = new Renderer(*buffer, *camera);

    buffer->MakeColoredBackGround();

    vector<Geometry*> objects{  new Sphere(0.0f, 0.0f, 1.0f, 0.3f, LightIntensity(1.0f,0.0f,0.0f)),
                                new Sphere(-0.8f, 0.4f, 2.0f, 0.3f, LightIntensity(1.0f,1.0f,0.0f)), 
                                new Sphere(0.99f, 0.0f, 2.0f, 0.3f, LightIntensity(1.0f,0.0f,1.0f)), };

    renderer->Render(objects,2);

    int comp = 3;
    char const* filename = "testPerspective.png";
    stbi_write_png(filename, buffer->width, buffer->height, comp, buffer->data, 0);


    buffer->MakeColoredBackGround();
    renderer->SetCamera(*orthographic);
    renderer->Render(objects,2);

    filename = "testOrtographic.png";
    stbi_write_png(filename, buffer->width, buffer->height, comp, buffer->data, 0);

    cout << "tan: " << tan(45 * 3.14f/ 180.f) << "\n";

    delete camera, buffer, renderer;
    objects.clear();

    return 0;
}
