#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <glad/glad.h>
#include <string>

namespace gpx
{
    class ShaderLoader
    {
        public:
            ShaderLoader(const std::string& filepath, uint32_t w, uint32_t h);
            virtual ~ShaderLoader();

            void Bind();
            void UpdateTime(unsigned const int timeTickes);
            void UpdateScroll(float zoomFactor);
            void UpdateRotate(float rotateDelta);

        private:
            uint32_t m_width;
            uint32_t m_height;

            uint32_t m_program;
            uint32_t m_shader[2];

    };
}

#endif