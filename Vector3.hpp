#pragma once
class Vector3
{
public:
    Vector3();
    Vector3(float x, float y, float z);

    Vector3 operator += (Vector3& b);
    Vector3 operator -= (Vector3& b);

    Vector3 operator += (Vector3 b);
    Vector3 operator -= (Vector3 b);
    Vector3 operator *= (float k);
    Vector3 operator /= (float k);

    Vector3 operator + (Vector3 &b);
    Vector3 operator - (Vector3& b);
    Vector3 operator * (float k);
    Vector3 operator / (float k);

    Vector3 operator - ();
    Vector3 operator + ();

    Vector3 Cross(Vector3& b);
    float Dot(Vector3& b);

    float Magnitude(Vector3& a);
    float SquerMagnitude(Vector3& a);
    float Magnitude();

//private:
    float x;
    float y;
    float z;
};

