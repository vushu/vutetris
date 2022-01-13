#include <bismuth/sprite.hpp>
#include <memory>

using namespace bi;

Sprite::Sprite(std::shared_ptr<Texture> texture) {
    this->texture = std::move(texture);
    construct();
}

Sprite::Sprite() {
    this->construct();
}

Sprite::Sprite(std::string filepath) {
    this->filepath = filepath;
    construct();
}


Sprite::~Sprite() {}

void Sprite::construct() {
    this->texCoords.push_back(glm::vec2(1,1));
    this->texCoords.push_back(glm::vec2(1,0));
    this->texCoords.push_back(glm::vec2(0,0));
    this->texCoords.push_back(glm::vec2(0,1));
}

int Sprite::getTextureId() {
    if (this->texture)
        return texture->textureId;
    else return -1;
}

void Sprite::setTexture(std::shared_ptr<Texture> texture) {
    this->texture = std::move(texture);
}

void Sprite::setTexCoords(std::vector<glm::vec2> texCoords) {
    this->texCoords = texCoords;
}

std::vector<glm::vec2> Sprite::getTexCoords() {
    return this->texCoords;
}

std::shared_ptr<Texture> Sprite::getTexture() {
    return this->texture;
}

std::string Sprite::getTextureFilePath() {
    return this->filepath;
}

