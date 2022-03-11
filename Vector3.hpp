#pragma once

#include <string>

class Vector3
{
public:
    Vector3();
    Vector3(float x, float y, float z);

    Vector3& operator += (Vector3& b);
    Vector3& operator -= (Vector3& b);
           
    //Vector3& operator += (Vector3 b);
    //Vector3& operator -= (Vector3 b);
    Vector3& operator *= (float k);
    Vector3& operator /= (float k);

    Vector3 operator + (Vector3& b);
    Vector3 operator - (Vector3& b);
    Vector3 operator * (float k);
    Vector3 operator / (float k);

    Vector3 operator - ();
    Vector3 operator + ();

    static Vector3 Cross(Vector3& a, Vector3& b);
    static float Dot(Vector3& a, Vector3& b);
    
    static float Magnitude(Vector3& a);
    static float SqrMagnitude(Vector3& a);

    float Magnitude();
    float SqrMagnitude();

    static Vector3 Normalize(Vector3 &a);
    Vector3 Normalize();

    std::string ToString();

    float x;
    float y;
    float z;
};

