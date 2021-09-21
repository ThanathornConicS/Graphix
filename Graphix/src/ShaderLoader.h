#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <glad/glad.h>
#include <string>
#include "Camera.h"
#include "Mouse.h"

namespace gpx
{
    class ShaderLoader
    {
        public:
            ShaderLoader(const std::string& filepath, __UINT32_TYPE__ w, __UINT32_TYPE__ h);
            virtual ~ShaderLoader();

            void Bind();
            void UpdateTime(unsigned const int timeTickes);
            void UpdateCamera(Camera cam);
            void UpdateMouse(Mouse mouse);

        private:
            __UINT32_TYPE__ m_width;
            __UINT32_TYPE__ m_height;

            __UINT32_TYPE__ m_program;
            __UINT32_TYPE__ m_shader[2];

    };
}

#endif