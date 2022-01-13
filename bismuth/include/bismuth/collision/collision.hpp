#pragma once
#include <glm/glm.hpp>
namespace bi {
    namespace collision {
        bool isPositionWithinRect(glm::vec2 position, glm::vec2 rectPos, glm::vec2 rectSize);
    }
}
