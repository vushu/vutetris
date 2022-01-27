#include "block.hpp"
#include "bismuth/iomanager.hpp"
#include "bismuth/logging.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"

using namespace blocks;

void Block::setBlock(std::string blockLetter)
{
    this->currentBlock = blockLetter;
}

void Block::setOffset(glm::vec2 offset)
{
    this->offset = offset;
}
void Block::incrementTilePos(glm::vec2 tilePos)
{
    bi::log("Incrementing with", tilePos);
    this->tilePos += tilePos;
    bi::log("New incremented with", this->tilePos);
}

void Block::setTilePos(glm::vec2 tilePos)
{
    this->tilePos = tilePos;
}

glm::vec2 Block::getTilePos()
{
    return this->tilePos;
}

void Block::rotateLeft()
{

}

void Block::setPosition(glm::vec2 position)
{
    this->position = position;
}

void Block::rotateRight() { }

void Block::draw()
{

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            int value = coords[row][col];
            //bi::log("col ", col);
            //bi::log("row ", row);
            //bi::log("val ", value);
            //bi::log("-----------");
            if (value == 1) {
                position = glm::vec2 { col * tileSize, row * tileSize } + glm::vec2 { tilePos.x * tileSize, tilePos.y * tileSize };
                bi::ioManager().renderer->drawQuad(offset + glm::vec2 { position.x, position.y }, { tileSize, tileSize }, letterColor);
            }
        }
    }
}
