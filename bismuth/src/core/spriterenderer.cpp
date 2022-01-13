#include <glm/ext/matrix_transform.hpp>
#include <bismuth/logging.hpp>
#include <bismuth/spriterenderer.hpp>
#include <glm/glm.hpp>
#include <string>

using namespace bi;

SpriteRenderer::SpriteRenderer(std::unique_ptr<Sprite> sprite) {
    this->mSprite = std::move(sprite);
    this->color = glm::vec4(1,1,1,1);
    this->position = glm::vec2(0,0);
    this->angle = 0.0f;
    this->scale = glm::vec2(225,225);
}

SpriteRenderer::~SpriteRenderer() {}


void SpriteRenderer::setColor(glm::vec4 color) {
    bi::log("setting color");
    this->color = color;
    this->isDirty = true;
}

std::vector<glm::vec2> SpriteRenderer::getTexCoords() {
    return this->mSprite->getTexCoords();
}

void SpriteRenderer::setClean() {
    this->isDirty = false;
}

std::shared_ptr<Texture> SpriteRenderer::getTexture() {
    return this->mSprite->getTexture();
}

void SpriteRenderer::setPosition(glm::vec2 position) {
    this->position = position;
    this->isDirty = true;
}

void SpriteRenderer::setScale(glm::vec2 scale) {
    if (this->scale != scale) {
        this->scale = scale;
        isDirty = true;
    }
}
void SpriteRenderer::setTextureCoords(std::vector<glm::vec2> coords) {
    isDirty = true;
}

void SpriteRenderer::setRotation(float radian) {
    this->angle = radian;
    isDirty = true;
}

void SpriteRenderer::initTexture() {
    if (this->mSprite->getTexture() != nullptr)
        this->mSprite->getTexture()->init();
}

std::string SpriteRenderer::getTextureFilePath() {
    return this->mSprite->getTextureFilePath();
}

void SpriteRenderer::updateBuffer(QuadVertex* quadPtr) {

    glm::vec2 halfDims(this->scale * 0.5f);
    glm::vec2 tl(-halfDims.x, halfDims.y);
    glm::vec2 bl(-halfDims.x, -halfDims.y);
    glm::vec2 br(halfDims.x, -halfDims.y);
    glm::vec2 tr(halfDims.x, halfDims.y);

    float texId = 0.0f;

    glm::vec2 topLeft = rotatePoint(tl, angle) + halfDims + this->position;
    glm::vec2 botLeft = rotatePoint(bl, angle) + halfDims + this->position;
    glm::vec2 botRight = rotatePoint(br, angle) + halfDims + this->position;
    glm::vec2 topRight = rotatePoint(tr, angle) + halfDims + this->position;

    //log("pos_x" + std::to_string(this->position.x));
    //log("pos_y" + std::to_string(this->position.y));

    quadPtr->position = { botRight.x, botRight.y , 0.0f};
    quadPtr->color = color;
    quadPtr->texcoords = {getTexCoords().at(0)};
    quadPtr->texId = texId;
    quadPtr++;

    quadPtr->position = { topRight.x, topRight.y, 0.0f };
    quadPtr->color = color;
    quadPtr->texcoords = {getTexCoords().at(1)};
    quadPtr->texId = texId;
    quadPtr++;

    quadPtr->position = { topLeft.x, topLeft.y, 0.0f };
    quadPtr->color = color;
    quadPtr->texcoords = {getTexCoords().at(2)};
    quadPtr->texId = texId;
    quadPtr++;

    quadPtr->position = { botLeft.x, botLeft.y, 0.0f };
    quadPtr->color = color;
    quadPtr->texcoords = {getTexCoords().at(3)};
    quadPtr->texId = texId;
    quadPtr++;
}

glm::vec2 SpriteRenderer::rotatePoint(const glm::vec2& pos, float angle) {
    glm::vec2 newPos;
    newPos.x = pos.x * cos(angle) - pos.y * sin(angle);
    newPos.y = pos.x * sin(angle) + pos.y * cos(angle);
    return newPos;
}



