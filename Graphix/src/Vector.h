#ifndef _VECTOR_H
#define _VECTOR_H

#include <iostream>
#include <iomanip>

namespace gpx
{
    struct Vector
    {
        Vector(void);
        Vector(float _x, float _y, float _z);

        inline friend std::ostream& operator<<(std::ostream& out, const Vector& vec)
        {
            out << std::fixed<<std::setprecision(4);
            out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
            return out;
        }

        float x;
        float y;
        float z;
    };
}

#endif