#include "bismuth/color.hpp"
#include "bismuth/iomanager.hpp"
#include <bismuth/gui/gui_label.hpp>
#include <bismuth/font.hpp>
#include <string>
using namespace bi::gui;

void GuiLabel::setFont(Font *font) {
    this->font = font;
}

void GuiLabel::setText(std::string text) {
    this->text = text;
    size = font->getSizeOfText(this->text, fontScale);
}

void GuiLabel::draw() {
    if (!visible)
        return;
    ioManager().renderer->drawText(this->text, this->position, *font, this->color, fontScale);
}

void GuiLabel::setColor(glm::vec4 color)  {
    this->color = color;
}
