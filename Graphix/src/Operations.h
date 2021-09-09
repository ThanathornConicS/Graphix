#ifndef _OPERATION_H
#define _OPERATION_H

#include "Vector.h"

using namespace gpx;

Vector operator+(const Vector& u, const Vector& v);
Vector operator-(const Vector& u, const Vector& v);
Vector operator-(const Vector& v);
Vector operator*(float n, const Vector& v);
Vector operator*(const Vector& v, float n);

float Dot(const Vector& u, const Vector& v);
Vector Cross(const Vector& u, const Vector& v);
float Magnitude(const Vector& v);
Vector Normalize(const Vector& v);

#endif