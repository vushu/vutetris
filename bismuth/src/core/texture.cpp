#include "bismuth/glhelper.hpp"
#include "bismuth/logging.hpp"
#include <bismuth/texture.hpp>
#include <glad/glad.h>

using namespace bi;

Texture::Texture(std::string filepath) {
    this->filepath = filepath;
}

Texture::~Texture() {
    bi::log("Texture destroyed " + this->filepath);
}

void Texture::init() {
    if (width != 0){
        filepath = "Generated Empty Texture";
        bi::log("Empty Texture initialized: ");
        textureId = glhelper::generateEmptyTexture(width, height);
        return;
    }


    glhelper::TextureInfo textureInfo = glhelper::generateTexture(this->filepath);
    this->textureId = textureInfo.textureId;
    this->width = textureInfo.width;
    this->height = textureInfo.height;

    bi::log("Texture initialized: " + filepath);
    bi::log("Texture Id: " + std::to_string(textureId));
    bi::log("Texture Width: " + std::to_string(this->width));
    bi::log("Texture Height: " + std::to_string(this->height));
}

void Texture::bind() {
    //log("TextureID: " + std::to_string(textureId));
    glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

std::array<glm::vec2, 4> Texture::getTexCoords(int tileNumber, glm::vec2 tilesize) {

    glm::vec2 tileCount { this->width/tilesize.x, this->height / tilesize.y };
    int x = tileNumber % (int) tileCount.x;
    int y = tileNumber / tileCount.x;
    x = x * tilesize.x;
    y = y * tilesize.y;

    return std::array<glm::vec2,4> {
        glm::vec2((float)(x + tilesize.x) / width, (float) (y + tilesize.y) /  height), // br
        glm::vec2((float)(x + tilesize.x) / width, (float) y / height), // tr
        glm::vec2((float) x / width, (float) y / height), // tl
        glm::vec2((float) x / width, (float)(y + tilesize.y) / height) // bl
    };
}
