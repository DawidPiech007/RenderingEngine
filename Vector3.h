#pragma once

#include <string>
#define EPSILON 0.0000001f

class Vector3
{
public:
    union
    {
        struct
        {
            float x;
            float y;
            float z;
        };
        struct
        {
            float r;
            float g;
            float b;
        };
            float p[3];
    };
    

    Vector3();
    Vector3(float x, float y, float z);

    Vector3& operator += (const Vector3& b);
    Vector3& operator -= (const Vector3& b);
    Vector3& operator *= (float k);
    Vector3& operator /= (float k);

    Vector3 operator + (const Vector3& b)const;
    Vector3 operator - (const Vector3& b)const;
    Vector3 operator * (const Vector3& b)const;
    Vector3 operator * (float k)const;
    Vector3 operator / (float k)const;

    Vector3 operator - ();
    Vector3 operator + ();

    static Vector3 Cross(const Vector3& a, const Vector3& b);
    static float Dot(const Vector3& a, const Vector3& b);
    static Vector3 Reflect(const Vector3& incidentVec, const Vector3& normal);
    
    static float Magnitude(const Vector3& a);
    static float SqrMagnitude(const Vector3& a);

    float Magnitude()const;
    float SqrMagnitude()const;

    static Vector3 Normalize(const Vector3 &a);
    Vector3 Normalize();

    static Vector3 Zero();

    std::string ToString()const;

    
};

