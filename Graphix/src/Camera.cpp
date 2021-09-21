#include "Camera.h"

namespace gpx
{
    Camera::Camera(float x, float y, float z, float speed)
    {
    this->m_x = x;
    this->m_y = y; 
    this->m_z = z;
    this->m_speed = speed;
}

void Camera::Reset()
{
    m_x = m_y = m_z = 0;
}

void Camera::Update(float x, float y, float z)
{
    m_x = x;
    m_y = y; 
    m_z = z;
}

void Camera::OffsetUpdate(float x, float y, float z)
{
    m_x += x * m_speed;
    m_y += y * m_speed; 
    m_z += z * m_speed;
}
}