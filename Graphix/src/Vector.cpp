#include "Vector.h"

namespace gpx
{
    Vector::Vector(void)
    {
        x = y = z = 0;
    }
    Vector::Vector(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
}