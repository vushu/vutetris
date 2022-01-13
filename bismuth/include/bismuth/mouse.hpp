#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
namespace bi{
    enum class Mouse
    {
        LEFT_CLICK = GLFW_MOUSE_BUTTON_LEFT,
        RIGHT_CLICK = GLFW_MOUSE_BUTTON_RIGHT,
        MIDDLE_CLICK = GLFW_MOUSE_BUTTON_MIDDLE,

        RELEASE = GLFW_RELEASE,
        PRESS = GLFW_PRESS,
        HOLD = 2
    };
}
