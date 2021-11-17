#include "ShaderLoader.h"
#include <iostream>
#include <cstring>
#include <fstream>

namespace gpx
{
    static void CheckError(uint32_t shader, uint32_t flag, bool isProgram, const char* error_message)
    {
        GLint sucess = 0;
        char error[1024] = {0};

        if(isProgram)
            glGetProgramiv(shader, flag, &sucess);
        else
            glGetProgramiv(shader, flag, &sucess);

        if(sucess == GL_FALSE)
        {
            if (isProgram)
            {
                glGetProgramInfoLog(shader, sizeof(error), NULL, error);
                std::cout << error_message << " " << error << std::endl;
            }
            else
            {
                glGetProgramInfoLog(shader, sizeof(error), NULL, error);
                //std::cout << error_message << " " << error << std::endl;
            }
        }
    }

    static uint32_t CreateShader(const char* text, GLenum shaderType)
    {
        uint32_t shader = glCreateShader(shaderType);

        if(shader == 0)
            std::cerr << "Error: Cannot Create Shader" << std::endl;

        const char* shaderSource[1];
        GLint shaderSourceLength[1];

        shaderSource[0] = text;
        shaderSourceLength[0] = strlen(text);

        glShaderSource(shader, 1, shaderSource, shaderSourceLength);
        glCompileShader(shader);

        CheckError(shader, GL_COMPILE_STATUS, false, "Error: Problem(s) during shader compilation");

        return shader;
    }

    static std::string LoadShader(const char* filename)
    {
        std::ifstream file;
        file.open(filename);

        std::string output;
        std::string line;

        if(file.is_open()){
            while(file.good()){
                getline(file,line);
                output.append(line + "\n");
            }
        } else {
            std::cerr << "Unable to load shader: " << filename << std::endl;
        }
        return output;
    }

    ShaderLoader::ShaderLoader(const std::string& filepath, uint32_t w, uint32_t h)
    {
        m_width = w;
        m_height = h;

        m_program = glCreateProgram();

        m_shader[0] = CreateShader(LoadShader((filepath + ".vs").c_str()).c_str(), GL_VERTEX_SHADER);
        m_shader[1] = CreateShader(LoadShader((filepath + ".fs").c_str()).c_str(), GL_FRAGMENT_SHADER);

        for(size_t i = 0; i < 2; i++)
            glAttachShader(m_program, m_shader[i]);

        glBindAttribLocation(m_program, 0, "pos");
        glBindAttribLocation(m_program, 1, "texCoord");

        glLinkProgram(m_program);
        CheckError(m_program, GL_LINK_STATUS, true, "Error: Failed to link shader");

        glLinkProgram(m_program);
        CheckError(m_program, GL_VALIDATE_STATUS, true, "Error: Failed to validate shader");
    }
    ShaderLoader::~ShaderLoader()
    {
        for(size_t i = 0; i < 2; i++)
        {
            glDetachShader(m_program, m_shader[i]);
            glDeleteShader(m_shader[i]);
        }
        glDeleteProgram(m_program);
    }

    void ShaderLoader::Bind()
    {
        glUseProgram(m_program);
        GLint resolutionUniLoc = glGetUniformLocation(m_program, "SystemResolution");
        glUniform2f(resolutionUniLoc, m_width, m_height);
    }

    void ShaderLoader::UpdateTime(unsigned const int timeTickes)
    {
        GLint timeUniLoc = glGetUniformLocation(m_program, "SystemTime");
        glUniform1f(timeUniLoc, timeTickes);
    }
    void ShaderLoader::UpdateScroll(float zoomFactor)
    {
        GLint zoomUniLoc = glGetUniformLocation(m_program, "zoom");
        glUniform1f(zoomUniLoc, zoomFactor);
    }
    void ShaderLoader::UpdateRotate(float rotateDelta) 
    {
        GLint rotateUniLoc = glGetUniformLocation(m_program, "rotateRate");
        glUniform1f(rotateUniLoc, rotateDelta);
    }
}