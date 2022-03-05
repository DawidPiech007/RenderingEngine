#include <iostream>
#include "Vector3.hpp"

using namespace std;

int main()
{
    cout << "Hello World!\n";

    Vector3 a(1.0f, 2.0f, 3.0f);
    Vector3 b(1.0f, 1.0f, 1.0f);

    Vector3 c = a + b;

    cout << "x=" << c.x << " y=" << c.y << " z=" << c.z;

    return 0;
}
