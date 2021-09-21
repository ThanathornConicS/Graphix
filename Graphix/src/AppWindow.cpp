#include "AppWindow.h"
#include <iostream>

namespace gpx
{
    AppWindow* AppWindow::s_instance = nullptr;

    static void Cursor_Callback(GLFWwindow* window, double xpos, double ypos)
    {
        double xPos, yPos;
        glfwGetCursorPos(AppWindow::GetInstance().GetWindowInstance() ,&xPos, &yPos);

        AppWindow::GetInstance().mouse_posX = xPos;
        AppWindow::GetInstance().mouse_posY = yPos;
    }

    AppWindow::AppWindow(const char* name)
        : m_name(name)
    {}

    void AppWindow::InitWindow()
    {
        SetWindowSize(600, 600);
        SetWindowPos(800, 400);
        SetWindowName(m_name);

        if(glfwInit() != GLFW_TRUE)
        {
            std::cout << "Error: Cannot Initialized GLFW" << std::endl;
            return;
        }

        glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_window = glfwCreateWindow(m_width, m_height, m_name, NULL, NULL);

        if (!m_window)
        {
           std::cout << "Error: Failed to open GLFW window, check available version with GLView" << std::endl;
            return;
        }

        glfwMakeContextCurrent(m_window);
        glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);

        // GLAD
        if (!gladLoadGL()) 
        {
            std::cout << "Failed to initialize OpenGL context" << std::endl;
            return;
        }

        glfwMakeContextCurrent(m_window);
        glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetWindowPos(m_window, m_xpos, m_ypos);

        glfwSwapInterval(1);

        isRunning = true;
    }

    void AppWindow::Update()
    { 
        //glClearColor(0.8f, 0.4f, 1.0f , 0.7f);
        //glClear(GL_COLOR_BUFFER_BIT);
        // clear the z-buffer
        // glClearDepth(1);
        // glClear(GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(m_window);
    }

    void AppWindow::InputListener(Camera* cam, Mouse* mouse)
    {
        if(glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
        {
            cam->OffsetUpdate(0, 0, 1);
        }
        else if(glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
        {
            cam->OffsetUpdate(0, 0, -1);
        }
        else if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            isRunning = false;
        }

        glfwSetCursorPosCallback(m_window, Cursor_Callback);
        mouse->MoveMouse(mouse_posX, mouse_posY);

        glfwPollEvents();
    }

    void AppWindow::Exit()
    {
        glfwTerminate();
    }

    void AppWindow::SetWindowSize(int w, int h)
    {
        m_width = w;
        m_height = h;
    }
    void AppWindow::SetWindowPos(int x, int y)
    {
        m_xpos = x;
        m_ypos = y;
    }
    void AppWindow::SetWindowName(const char* n)
    {
        m_name = n;
    }


}