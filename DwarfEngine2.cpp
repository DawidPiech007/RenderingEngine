#include <iostream>
#include "Vector3.hpp"

using namespace std;

int main()
{
    cout << "Hello World!\n";

    Vector3 a(1.0f, 2.0f, 3.0f);
    Vector3 b(1.0f, 1.0f, 1.0f);

    Vector3 c = a/ 2.0f;

    c += (-b * 2.0f);

    cout << "x=" << c.x << " y=" << c.y << " z=" << c.z << endl;
    cout << "x=" << b.x << " y=" << b.y << " z=" << b.z << endl;

    return 0;
}
