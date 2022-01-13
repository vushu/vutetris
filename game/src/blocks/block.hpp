#pragma once
#include "bismuth/color.hpp"
#include "glm/fwd.hpp"
#include <array>
#include <map>
#include <string>
namespace blocks {
class Block {
public:
    Block(glm::vec2 initPos, glm::vec4 color, glm::mat4 tileSpaces)
        : letterColor(color)
        , coords(tileSpaces) {};
    ~Block() {};
    void setBlock(std::string blockLetter);
    void draw();
    void setOffset(glm::vec2 position);

    void incrementTilePos(glm::vec2 tilePos);

    void setTilePos(glm::vec2 tilePos);
    glm::vec2 getTilePos();

private:
    std::string currentBlock = "L";
    int tileSize = 16.0f;
    glm::vec4 letterColor;
    glm::vec2 offset = glm::vec2 { 0.0f, 0.0f };
    glm::mat4 coords;
    glm::vec2 tilePos = { 0, 0 };
};
}
