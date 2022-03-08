#include <iostream>
#include "Vector3.hpp"

using namespace std;

int main()
{
    Vector3 a(1.0f, 0.0f, 0.0f);
    Vector3 b(1.0f, 0.0f, 0.0f);
    cout << "a\n" << a.ToString();
    cout << "b\n" << b.ToString();

    float dot = Vector3::Dot(a, b);
    Vector3 cross = Vector3::Cross(a,b);

    cout << "dot\n  " << dot << "\n";
    cout << "cross\n" << cross.ToString();
    

    return 0;
}
