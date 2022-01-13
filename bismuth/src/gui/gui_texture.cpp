#include "bismuth/iomanager.hpp"
#include <bismuth/gui/gui_texture.hpp>
using namespace bi::gui;

void GuiTexture::init() {
    Texture& texture = ioManager().assetmanager->getTexture(this->filepath);
    this->textureId = texture.textureId;
    this->size = { texture.width, texture.height };
}

void GuiTexture::setColor(glm::vec4 color) {
    this->color = color;
}

void GuiTexture::draw() {
    ioManager().renderer->drawTexture(this->position, size, color, textureId);
}
