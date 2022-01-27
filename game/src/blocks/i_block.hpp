#pragma once
#include "glm/fwd.hpp"
#include <vector>
class IBlock {
public:
    // constructors, assignment, destructor
    IBlock();
    ~IBlock();

private:
    std::vector<glm::mat4> rotations;
};
