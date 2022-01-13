#include "bismuth/collision/collision.hpp"

bool bi::collision::isPositionWithinRect(glm::vec2 position, glm::vec2 rectPos, glm::vec2 rectSize) {
    return
        position.x >= rectPos.x &&
        position.x <= rectPos.x + rectSize.x
        && position.y >= rectPos.y &&
        position.y <= rectPos.y + rectSize.y;
}
