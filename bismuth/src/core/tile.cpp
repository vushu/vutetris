#include "bismuth/logging.hpp"
#include <bismuth/tile.hpp>
#include <limits>
using namespace bi;

Tile::~Tile() {}

void Tile::setup() {

    int nRows = (int)(imageSize.x / tileSize.x);
    int nCols = (int)(imageSize.y / tileSize.y);

    int posX = id % nRows;
    int posY = (int)(id / nCols);

    posX = posX * tileSize.x;
    posY = posY * tileSize.y;

    glm::vec2 dimension {imageSize.x, imageSize.y};
    glm::vec2 br{(float)(posX + tileSize.x), (float)(posY + tileSize.y)};
    glm::vec2 tr{(float)(posX + tileSize.x), (float)(posY)};
    glm::vec2 tl{(float)posX, (float)(posY)};
    glm::vec2 bl{(float)posX, (float)(posY + tileSize.y)};
    this->texCoords = {
        br / dimension, //BR
        tr / dimension, //TR
        tl / dimension, //TL
        bl / dimension  //BL
    };
}

void Tile::animate() {
    bi::log("animated sprite not implemented");
}

std::array<glm::vec2, 4> Tile::getTexCoords() {

    return this->texCoords;
}

glm::vec2 Tile::getPosition() {
    return this->position;
}

void Tile::setPosition(glm::vec2 pos) {
    this->position = pos;
}

unsigned int Tile::getTextureId() {
    return this->texId;
}

unsigned int Tile::getId() {
    return this->id;
}

glm::vec2 Tile::getTileSize() {
    return this->tileSize;
}

glm::vec2 Tile::getTileCell() {
    return {static_cast<int>(this->position.x/tileSize.x), static_cast<int>(this->position.y/tileSize.y)};
}

bool Tile::isEmpty()  {
    return id == std::numeric_limits<unsigned int>::max();
}
