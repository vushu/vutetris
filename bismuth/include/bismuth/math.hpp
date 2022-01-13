#pragma once
#include <glm/glm.hpp>

namespace bi {
    namespace math {
        float degreesToRadians(float degrees);
        float radiansToDegrees(float radians);
        float clamp(float min, float max, float value);
        glm::vec2 clamp(glm::vec2 min, glm::vec2 max, glm::vec2 value);
    }
}

