#include <algorithm>
#include <bismuth/math.hpp>
#define M_PI 3.14159265358979323846
namespace bi {

    float math::degreesToRadians(float degrees) {
        return (degrees * M_PI) / 180.0f;
    }

    float math::radiansToDegrees(float radians) {
        return (radians * 180.0f) / M_PI;
    }

    float math::clamp(float min, float max, float value) {
        return std::min(std::max(min, value), max);
    }

    glm::vec2 math::clamp(glm::vec2 min, glm::vec2 max, glm::vec2 value) {
        return {clamp(min.x, max.x, value.x), clamp(min.y, max.y, value.y)};
    }
}
