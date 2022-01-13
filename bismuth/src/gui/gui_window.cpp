#include "bismuth/assetmanager.hpp"
#include "bismuth/color.hpp"
#include "bismuth/iomanager.hpp"
#include "bismuth/math.hpp"
#include "bismuth/mouselistener.hpp"
#include <bismuth/gui/gui_window.hpp>
#include <bismuth/collision/collision.hpp>
using namespace bi;
using namespace gui;

GuiWindow& GuiWindow::setSize(glm::vec2 size) {
    this->size = size;
    return *this;
}

GuiWindow& GuiWindow::setOutlineWidth(float outlineWidth) {
    this->outlineWidth = outlineWidth;
    return *this;
}

GuiWindow& GuiWindow::setBackgroundColor(glm::vec4 color)  {
    this->backgroundColor = color;
    return *this;
}

GuiWindow& GuiWindow::setOutlineColor(glm::vec4 color)  {
    this->outlineColor = color;
    return *this;
}

glm::vec2 GuiWindow::positionBottomRight(glm::vec2 size) {
    return {this->position.x + this->size.x - size.x, this->position.y + this->size.y - size.y};
}

glm::vec2 GuiWindow::positionTopRight(glm::vec2 size) {
    return {this->position.x + this->size.x - size.x, this->position.y + size.y};
}

void GuiWindow::draw() {
    ioManager().renderer->drawQuad(this->position, this->size, backgroundColor);
    ioManager().shaperenderer->setLineWidth(this->outlineWidth);
    ioManager().shaperenderer->drawRect(this->position, this->size, outlineColor).endFlushBegin();

    for (auto& child : children){
        child->draw();
    }
}

bool GuiWindow::handleMouseClick(int action, glm::vec2 position) {
    if (isClosed) {
        return false;
    }

    if (action == GLFW_MOUSE_BUTTON_LEFT){
        isMouseOver = isPositionWithinRect(position);
    }
    return isMouseOver;
}

bool GuiWindow::mouseClicked() {
    if (bi::mouseInput().mouseButtonDown(GLFW_MOUSE_BUTTON_LEFT) && !isMouseOver) {
        isMouseOver = true;
        handleMouseClick(GLFW_MOUSE_BUTTON_LEFT, bi::mouseInput().getPosition());
    }
    return isMouseOver;
}

bool GuiWindow::mouseReleased() {

    if (!isMouseOver) {
        mouseClicked();
    }

    else if (!bi::mouseInput().mouseButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
        isMouseOver = false;
    }
    return isMouseOver;
}


void GuiWindow::close() {
    this->isClosed = true;
}

void GuiWindow::show() {
    this->isClosed = false;
}

void GuiWindow::onMouseOver(GuiWindowCallback callback) {
    this->mouseOverCallback = callback;
}


void GuiWindow::dragging() {

    if (!isMouseOver) {
        mouseReleased();
    }

    glm::vec2 mouse = {bi::mouseInput().toOrthoX(), bi::mouseInput().toOrthoY()};

    if (!isDragging && isMouseOver) {
        windowMouseDiff = this->position - mouse;
        if (this->isPositionWithinRect(mouse)){
            isDragging = true;
        }
    }

    if (isMouseOver) {
        this->setPosition(mouse + windowMouseDiff);
    }
}

void GuiWindow::draggingEnd() {

    if (isDragging) {
        this->isDragging = false;
        this->isMouseOver = false;
    }
}

void GuiWindow::processDragging() {

    if (bi::mouseInput().isDragging) {
        dragging();
    }

    else if (!bi::mouseInput().isDragging) {
        draggingEnd();
    }
}

void GuiWindow::processInput() {
    handleMouseOver();
    for (auto& child : children) {
        child->processInput();
    }
}

void GuiWindow::handleMouseOver() {
    if (isPositionWithinRect(mouseInput().getPosition())){

        if (mouseOverCallback && !isMouseOver) {
            isMouseOver = true;
            mouseOverCallback(*this);
        }
    }
    else if (mouseOverCallback && isMouseOver){
        isMouseOver = false;
        mouseOverCallback(*this);
    }

}
