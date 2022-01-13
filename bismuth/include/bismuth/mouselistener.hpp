#pragma once
#include "bismuth/window.hpp"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <memory>
#include "camera.hpp"
namespace bi {

    class MouseListener{
        public:
            static void mousePosCallback(GLFWwindow* window, double xPos, double yPos);
            static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
            static void mouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
            static float toOrthoX(int width);
            static float toOrthoY(int height);
            static float toOrthoX();
            static float toOrthoY();
            static MouseListener& get() {
                static MouseListener instance;
                return instance;
            }

            static bool mouseButtonDown(int button) {
                if (button < numberOfMouseButtons) {
                    return get().mouseButtonPressed[button];
                }
                return false;
            }
            static bool mouseButtonClicked(int button) {
                if (button < numberOfMouseButtons) {
                    bool res = get().mouseButtonPressed[button];
                    get().mouseButtonPressed[button] = false;
                    return res;
                }
                return false;
            }

            static glm::vec2 getPosition() {
                return {toOrthoX(), toOrthoY()};
            }

            static const int numberOfMouseButtons = 9;
            bool mouseButtonPressed[numberOfMouseButtons] = {false};
            void hideCursor();
            void showCursor();
            ~MouseListener();
            double scrollX, scrollY;
            double xPos = -1, yPos = -1;
            bool isDragging;
        private:
            MouseListener();


    };
    MouseListener& mouseInput();
}
