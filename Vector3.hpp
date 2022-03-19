#pragma once

#include <string>

class Vector3
{
public:
    Vector3();
    Vector3(float x, float y, float z);

    Vector3& operator += (const Vector3& b);
    Vector3& operator -= (const Vector3& b);
           
    //Vector3& operator += (Vector3 b);
    //Vector3& operator -= (Vector3 b);
    Vector3& operator *= (float k);
    Vector3& operator /= (float k);

    Vector3 operator + (const Vector3& b)const;
    Vector3 operator - (const Vector3& b)const;
    Vector3 operator * (float k)const;
    Vector3 operator / (float k)const;

    Vector3 operator - ();
    Vector3 operator + ();

    static Vector3 Cross(const Vector3& a, const Vector3& b);
    static float Dot(const Vector3& a, const Vector3& b);
    
    static float Magnitude(const Vector3& a);
    static float SqrMagnitude(const Vector3& a);

    float Magnitude()const;
    float SqrMagnitude()const;

    static Vector3 Normalize(const Vector3 &a);
    Vector3 Normalize();

    std::string ToString()const;

    float x;
    float y;
    float z;
};

