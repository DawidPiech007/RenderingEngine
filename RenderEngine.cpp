#include <iostream>
#include "Vector3.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Buffer.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "LightIntensity.hpp"

using namespace std;

int main()
{
    Vector3 a(2.0f, 3.0f, 4.0f);

    Sphere s(0.0f, 0.0f, 0.0f, 10.0f);
    Ray r1(Vector3(0.0f, 0.0f, -20.0f), Vector3(0.0f, 0.0f, 40.0f));

    Buffer* buffer = new Buffer(600, 600);
    buffer->FillColor(0, 0, 0);
   // buffer->MakeColoredBackGround();


    vector<Vector3*> v;
    Sphere sphere(0.0f, 0.0f, 6.0f, 1.0f);
    //Ray ray(Vector3(0, 0, -4), Vector3(midX, midY, 0));

    float pixelWitdh = 2.0f / 600;
    float pixelHeight = 2.0f / 600;

    for (int i = 0; i < 600; i++)
    {
        for (int j = 0; j < 600; j++)
        {
            float midX = -1.f + (i+ 0.5f) * pixelHeight;
            float midY =  1.f - (j + 0.5f) * pixelWitdh;
           // std::cout << "midX "<<midX<<"\n";
            //std::cout << "midY " << midY << "\n";
            Ray ray(Vector3(midX, midY, 0), Vector3(0, 0, 1));
            //Ray ray1(Vector3(midX, midY, -1), Vector3(midX, midY, 0));
            v = sphere.IntersectPoints(ray);
            if (v.size() != 0) {
                buffer->SetColor(i, j, 255, 255, 0);
                //std::cout << "INTERSECT"<<v[0]->ToString() <<"\n";
            }
            else {
                buffer->SetColor(i, j, 0, 100, 100);
            }

        }
    }

    int comp = 3;
    char const* filename = "test01.png";
    stbi_write_png(filename, buffer->width, buffer->height, comp, buffer->data, 0);

    return 0;
}
