#pragma once
#include <glm/glm.hpp>
namespace bi {
    namespace color {
        glm::vec4 fromRGB(glm::vec4 color);
        glm::vec4 fromRGB(float r, float g, float b, float a);
        const glm::vec4 WHITE {1,1,1,1};
        const glm::vec4 BLACK {0,0,0,1};
        const glm::vec4 CORNFLOWER_BLUE {fromRGB(100, 149, 237, 1)};
        const glm::vec4 SOFT_RED {fromRGB(237, 100, 114, 1)};
        const glm::vec4 SOFT_BLUE {fromRGB(100, 114, 237, 1)};
        const glm::vec4 SOFT_GREEN {fromRGB(114, 237, 100, 1)};
        const glm::vec4 SOFT_MAGENTA {fromRGB(223, 100, 237,1)};
        const glm::vec4 SOFT_YELLOW {fromRGB(237, 223, 100,1)};
        const glm::vec4 SOFT_ORANGE {fromRGB(237, 155, 100, 1)};
    }
}
