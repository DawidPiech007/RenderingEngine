#include <iostream>
#include "Vector3.hpp"
#include "Ray.hpp"

using namespace std;

int main()
{
    Vector3 a(2.0f, 3.0f, 4.0f);
    Vector3 b(5.0f, 6.0f, 7.0f);
    Vector3 c(5.0f, 6.0f, 7.0f);

    c = c.Normalize();

    Ray ray(a, b);

    cout << "normalized\n" << c.ToString() << "\n";

    return 0;
}
