#include <iostream>
#include "Vector3.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"

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

    Vector3 o1(0.0f, 0.0f, -20.0f);
    Vector3 d1(0.0f, 0.0f, 40.0f);
    Ray r1(o1, d1);

    vector<Vector3*> contactPoints = s.Intersect(r1);

    cout << "contactPoints1\n" << contactPoints[0]->ToString() << "\n";
    cout << "contactPoints2\n" << contactPoints[1]->ToString() << "\n";

    return 0;
}
