#ifndef MOUSE_H
#define MOUSE_H

namespace gpx
{
    class Mouse 
    {
        public:
            Mouse(float x, float y);
            void MoveMouse(float x, float y);

            inline float GetAngleX()
            { 
                return m_x;
            }
            inline float GetAngleY()
            { 
                return m_y;
            }
        private:
            float m_x, m_y;
    };
}

#endif