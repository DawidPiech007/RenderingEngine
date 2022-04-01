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
#include "Triangle.h"

using namespace std;

int main()
{
    Buffer* buffer = new Buffer(1080, 1080);
    Camera* camera = new Camera();
    camera->SetFOV(60);
    CameraOrthographic* orthographic = new CameraOrthographic();
    RENDERER.SetUp(*buffer, *camera, 0.126); // 1/8 + 0.001 czyli rekurencja pójdzie 4 razy w dół

    buffer->MakeColoredBackGround();

    Vector3 v1(-1, -1, 5);
    Vector3 v2(1, -1, 5);
    Vector3 v3(0, 1, 5);

    Triangle t(v1, v2, v3, LightIntensity(0.8f, 0.4f, 0.2f));


    vector<Geometry*> objects{ new Sphere(0.0f, 0.0f, 9.0f, 0.3f, LightIntensity(1.0f, 0.0f, 0.0f)),
                                new Sphere(-0.1f, 0.0f, 9.0f, 0.3f, LightIntensity(1.0f, 1.0f, 0.0f)),
                                new Sphere(0.2f, 0.0f, 9.0f, 0.3f, LightIntensity(1.0f, 0.0f, 1.0f)),
                                &t };

    RENDERER.Render(objects);

    int comp = 3;
    char const* filename = "testPerspective.png";
    stbi_write_png(filename, buffer->width, buffer->height, comp, buffer->data, 0);


    buffer->MakeColoredBackGround();
    RENDERER.SetCamera(*orthographic);
    RENDERER.Render(objects);

    filename = "testOrtographic.png";
    stbi_write_png(filename, buffer->width, buffer->height, comp, buffer->data, 0);



    delete camera, orthographic, buffer, RENDERER;
    objects.clear();


    return 0;
}
