#ifndef CAMERA_H
#define CAMERA_H

namespace gpx
{
    class Camera
    {
        public:
            Camera(float x,float y, float z, float speed);

            void Reset();
            void Update(float x,float y,float z);
            void OffsetUpdate(float x, float y, float z);

            inline float GetX() const
            {
                return m_x;
            }
            inline float GetY() const 
            {
                return m_y;
            }
            inline float GetZ() const
            {
                return m_z;
            }

        private:
            float m_x, m_y, m_z, m_speed;

    };
}

#endif