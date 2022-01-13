#pragma  once
#include <glm/glm.hpp>
namespace bi {

    struct QuadVertex {
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 texcoords;
        float texId;
        float type;
    };

    struct SimpleVertex {
        glm::vec3 position;
        glm::vec4 color;
    };
}
