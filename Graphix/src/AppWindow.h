#ifndef APPWINDOW_H
#define APPWINDOW_H

#include "ShaderLoader.h"
#include <GLFW/glfw3.h>

namespace gpx
{
    class AppWindow
    {
        public:
            inline static AppWindow& GetInstance()
            {
                if(!s_instance)
                    s_instance = new AppWindow("DEFAULT");

                return *s_instance;
            }

            AppWindow(AppWindow &other_instance) = delete;
            void operator=(const AppWindow&) = delete;

            inline const char* GetName() const
            {
                return m_name;
            }
            inline int GetWidth() const
            {
                return m_width;
            }
            inline int GetHeight() const
            {
                return m_height;
            }
            inline bool GetRunningStatus() const
            {
                return isRunning;
            }

            void InitWindow();
            void Update();
            void InputListener();
            void Exit();

            void SetWindowSize(int w, int h);
            void SetWindowPos(int x, int y);
            void SetWindowName(const char* n);

            inline GLFWwindow* GetWindowInstance() const
            {
                return m_window;
            }

        public:
            float mouse_posX, mouse_posY;
            double zoom_factor = 2;

        protected:    
            AppWindow(const char* name);

        private:
            static AppWindow* s_instance;
            GLFWwindow* m_window;

            int m_width, m_height;
            int m_xpos, m_ypos;
            const char* m_name; 

            bool isRunning = false;
    };
}

#endif