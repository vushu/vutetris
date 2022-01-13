#pragma once
#include "glm/fwd.hpp"
#include <GLFW/glfw3.h>
#include <string>
namespace  bi {
    class Window{
        public:
            // constructors, asssignment, destructor
            Window(std::string title);
            Window(int width, int height, std::string title);
            ~Window();
            void init();
            bool windowShouldClose();
            void pollEvents();
            void close();
            GLFWwindow* window;
            int width = 0;
            int height = 0;
            void swapBuffers();
            int maxWidth;
            int maxHeight;
            glm::vec2 maxSize();
            glm::vec2 size();
            void fullscreen();
            void fullscreen(int width, int height);
            void windowed(int width, int height);
            void destroy();
            bool isFullscreen = false;

        private:

            void getResolution();
            void setupCallbacks();
            static void resizeWindowCallback(GLFWwindow* window, int width, int height);
            static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
            //void errorCallback(int error, const char* description);
            void configureOpenGL();
            std::string title;
    };
}
