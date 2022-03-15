#include <iostream>
#include "Vector3.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Buffer.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;

int main()
{
    Vector3 a(2.0f, 3.0f, 4.0f);
    Vector3 b(5.0f, 6.0f, 7.0f);
    Vector3 c(5.0f, 6.0f, 7.0f);

    c = c.Normalize();

    Ray ray(a, b);

    cout << "normalized\n" << c.ToString() << "\n";



    Sphere s(0.0f, 0.0f, 0.0f, 10.0f);
    Ray r1(Vector3(0.0f, 0.0f, -20.0f), Vector3(0.0f, 0.0f, 40.0f));
    Ray r2(Vector3(0.0f, 0.0f, -20.0f), Vector3(0.0f, 100.0f, 0.0f));
    Ray r3(Vector3(0.0f, 10.0f, -20.0f), Vector3(0.0f, 0.0f, 40.0f));
    Ray r4(Vector3(0.0f, 0.0f, 0.0f), Vector3(100.0f, 100.0f, 100.0f));

    vector<Vector3*> contactPoints_r1_s = s.Intersect(r1);
    vector<Vector3*> contactPoints_r2_s = s.Intersect(r2);
    vector<Vector3*> contactPoints_r3_s = s.Intersect(r3);
    vector<Vector3*> contactPoints_r4_s = s.Intersect(r4);

    cout << "contactPoints_r1_s (" << contactPoints_r1_s.size() << ")\n";
    cout << contactPoints_r1_s[0]->ToString() << "\n";
    cout << contactPoints_r1_s[1]->ToString() << "\n";

    cout << "contactPoints_r2_s (" << contactPoints_r2_s.size() << ")\n";
    cout << "\n";

    cout << "contactPoints_r3_s (" << contactPoints_r3_s.size() << ")\n";
    cout << contactPoints_r3_s[0]->ToString() << "\n";

    cout << "contactPoints_r4_s (" << contactPoints_r4_s.size() << ")\n";
    cout << contactPoints_r4_s[0]->ToString() << "\n";

    Vector3 q1(0.0f, 0.0f, 0.0f);
    Vector3 q2(0.0f, 1.0f, 1.0f);

    Plane plane(q1, q2);
    vector<Vector3*> contactPoints_r1_p = plane.Intersect(r2);
    cout << "contactPoint_r2_p (" << contactPoints_r4_s.size() << ")\n";
    cout << contactPoints_r1_p[0]->ToString() << "\n";

    Buffer* buffer = new Buffer(200, 100);
    buffer->FillColor(255, 255, 255);

    int comp = 3;
    char const* filename = "test01.png";
    stbi_write_png(filename, buffer->width, buffer->height, comp, buffer->data, 0);

    return 0;
}
