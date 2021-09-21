#include <iostream>
#include "AppWindow.h"
#include "ShaderLoader.h"
#include "Mesh.h"

gpx::AppWindow* app_window = nullptr;

int main(int argc, char* argv[])
{
    app_window = &gpx::AppWindow::GetInstance();
    
    app_window->InitWindow();

    gpx::ShaderLoader shader("../shaders/fractals", (__UINT32_TYPE__)app_window->GetWidth(), (__UINT32_TYPE__)app_window->GetHeight());

    gpx::Vertex vertices[] = 
    {
        gpx::Vertex(glm::vec3(-1, 1, 0), glm::vec2(0, 0)),
        gpx::Vertex(glm::vec3(1, 1, 0), glm::vec2(1, 0)),
        gpx::Vertex(glm::vec3(-1, -1, 0), glm::vec2(0, 1)),
        gpx::Vertex(glm::vec3(1, 1, 0), glm::vec2(1, 1))
    };

    gpx::Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));

    gpx::Camera camera(0, 0, -4, 1);
    gpx::Mouse mouse(0, 0);
    
    do
    {   
        glClearColor(0.8f, 0.4f, 1.0f , 0.3f);
        glClear(GL_COLOR_BUFFER_BIT);
        // clear the z-buffer
        glClearDepth(1);
        glClear(GL_DEPTH_BUFFER_BIT);

        shader.Bind();
        shader.UpdateTime(glfwGetTime() * 1000);
        shader.UpdateCamera(camera);
        shader.UpdateMouse(mouse);
        mesh.Draw();
        app_window->InputListener(&camera, &mouse);
        app_window->Update();
    
    } while (app_window->GetRunningStatus() == true);

    
    app_window->Exit();

    return 0;
}