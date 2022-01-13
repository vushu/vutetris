#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "bismuth/keyboard.hpp"
#include <memory>
#include <bitset>
namespace bi {

    class KeyListener{
        public:
            // constructors, asssignment, destructor
            static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

            static KeyListener& get() {
                static KeyListener instance;
                return instance;
            }

            bool keyPressed[350] = {false};
            bool keyReleased[350] = {false};

            bool isKeyPressed(Key keyCode);
            void reset();

            bool isKeyReleased(Key keyCode);

            int lastKeyCode = -1;
            ~KeyListener();
        private:
            KeyListener();


    };
    KeyListener& keyInput();
}
