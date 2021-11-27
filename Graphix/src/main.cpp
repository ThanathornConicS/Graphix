#include <iostream>
#include "AppWindow.h"
#include "ShaderLoader.h"
#include "Mesh.h"

gpx::AppWindow* app_window = nullptr;

int main(int argc, char* argv[])
{
    app_window = &gpx::AppWindow::GetInstance();
    
    app_window->InitWindow();

    gpx::ShaderLoader shader("../shaders/fractals", (uint32_t)app_window->GetWidth(), (uint32_t)app_window->GetHeight());

    gpx::Vertex vertices[] = 
    {
        gpx::Vertex(glm::vec3(-1, 1, 0), glm::vec2(-1, -1)),
        gpx::Vertex(glm::vec3(1, 1, 0), glm::vec2(1, -1)),
        gpx::Vertex(glm::vec3(-1, -1, 0), glm::vec2(-1, 1)),
        gpx::Vertex(glm::vec3(1, -1, 0), glm::vec2(1, 1))
    };

    gpx::Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
    
    float rotRate = 5.0f;

    do
    {   
        glClearColor(0.6f, 0.1f, 0.6f , 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // clear the z-buffer 
        glClearDepth(1);
        glClear(GL_DEPTH_BUFFER_BIT);

        shader.Bind();
        shader.UpdateTime(glfwGetTime() * 1000);
        shader.UpdateScroll(app_window->zoom_factor);
        shader.UpdateRotate(cos(rotRate));
        mesh.Draw();
        app_window->InputListener();
        app_window->Update();

        rotRate += 0.001f;
    
    } while (app_window->GetRunningStatus() == true);

    
    app_window->Exit();

    return 0;
}