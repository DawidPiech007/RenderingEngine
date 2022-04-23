#include "ICamera.h"
#include "Ray.h"

Vector3 ICamera::GetPosition()
{
    return Vector3();
}

Vector3 ICamera::GetTarget()
{
    return Vector3();
}

Vector3 ICamera::GetUp()
{
    return Vector3();
}

Ray ICamera::GetRay(float u, float v)
{
    return Ray();
}

float ICamera::GetFOV()
{
    return 0.0f;
}
