#pragma once
class Vector3
{
public:
    Vector3();
    Vector3(float x, float y, float z);

    Vector3 operator + (Vector3 &b);

//private:
    float x;
    float y;
    float z;
};

