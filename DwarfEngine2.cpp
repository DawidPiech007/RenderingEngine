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

    return 0;
}
