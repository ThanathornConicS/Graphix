#include "ShaderLoader.h"
#include <iostream>
#include <cstring>
#include <fstream>

namespace gpx
{
    static void CheckError(__UINT32_TYPE__ shader, __UINT32_TYPE__ flag, bool isProgram, const char* error_message)
    {
        GLint sucess = 0;
        char error[1024] = {0};

        if(isProgram)
            glGetProgramiv(shader, flag, &sucess);
        else
            glGetProgramiv(shader, flag, &sucess);

        if(sucess == GL_FALSE)
        {
            if(isProgram)
                glGetProgramInfoLog(shader, sizeof(error), NULL, error);
            else
                glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        }
    }

    static __UINT32_TYPE__ CreateShader(const char* text, GLenum shaderType)
    {
        __UINT32_TYPE__ shader = glCreateShader(shaderType);

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
        std::ifstream file(filename);
        
        if(file.is_open())
        {
            std::string output;
            std::string line;

            while (file.good())
            {
                std::getline(file, line);
                output.append(line + "\n");   
            }

            return output;
        }
        else
        {
            std::cerr << "Error: Unable to load shader" << std::endl;
            return "";
        }
    }

    ShaderLoader::ShaderLoader(const std::string& filepath, __UINT32_TYPE__ w, __UINT32_TYPE__ h)
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
        GLint resolutionUniLoc = glGetUniformLocation(m_program, "systemResolution");
        glUniform2f(resolutionUniLoc, m_width, m_height);
    }

    void ShaderLoader::UpdateTime(unsigned const int timeTickes)
    {
        GLint timeUniLoc = glGetUniformLocation(m_program, "SystemTime");
        glUniform1f(timeUniLoc, timeTickes);
    }
    void ShaderLoader::UpdateCamera(Camera cam)
    {
        GLint camPosUniLoc = glGetUniformLocation(m_program, "camera_pos");
        glUniform3f(camPosUniLoc, cam.GetX(), cam.GetY(), cam.GetZ());
    }
    void ShaderLoader::UpdateMouse(Mouse mouse)
    {
        GLint mouseDeltaUniLoc = glGetUniformLocation(m_program, "mouse_delta");
        glUniform2f(mouseDeltaUniLoc, mouse.GetAngleX(), mouse.GetAngleY());
    }
}