#include <iostream>
#include <math.h>

#include "Operations.h"

Vector operator+(const Vector& u, const Vector& v)
{
    return Vector(u.x + v.x, u.y + v.y, u.z + v.z);    
}
Vector operator-(const Vector& u, const Vector& v)
{
    return Vector(u.x - v.x, u.y - v.y, u.z - v.z);    
}
Vector operator-(const Vector& v)
{
    return Vector(-v.x, -v.y, -v.z);    
}
Vector operator*(float n, const Vector& v)
{
    return Vector(n * v.x, n * v.y, n * v.z);    
}
Vector operator*(const Vector& v, float n)
{
    return n * v;    
}

float Dot(const Vector& u, const Vector& v)
{
    return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
}
Vector Cross(const Vector& u, const Vector& v)
{
    long retX, retY, retZ;

    retX = (u.y * v.z) - (u.z * v.y);
    retY = (u.z * v.x) - (u.x * v.z);
    retZ = (u.x * v.y) - (u.x * v.y);

    return Vector(retX, retY, retZ);
}
float Magnitude(const Vector& v)
{
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}
Vector Normalize(const Vector& v)
{
    return (1.0f / Magnitude(v)) * v;
}
