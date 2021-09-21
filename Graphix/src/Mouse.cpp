#include "Mouse.h"

namespace gpx
{
    Mouse::Mouse(float x,float y)
    {
        m_x = x;
        m_y = y;
    }

    void Mouse::MoveMouse(float x, float y)
    {
        m_x += x;
        m_y += y;
    }
}