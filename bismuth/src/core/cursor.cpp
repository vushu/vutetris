#include "bismuth/color.hpp"
#include "bismuth/iomanager.hpp"
#include "bismuth/logging.hpp"
#include "bismuth/mouselistener.hpp"
#include <bismuth/cursor.hpp>
using namespace bi;

Cursor::~Cursor() {

}

void Cursor::init(){
    this->cursorTextureId = bi::ioManager().assetmanager->loadTexture(cursorFilePath);
    this->currentTextCoord = pointerCursorTexcoords;
}

void Cursor::setColor(glm::vec4 color){
    this->color = color;
}

void Cursor::setMouseOver(bool enable) {
    isMouseOver = enable;
    if (isMouseOver) {
        currentTextCoord = mouseOverCursorTexcoords;
    }
    else
        currentTextCoord = pointerCursorTexcoords;
}

void Cursor::setTexture(std::string cursorFilePath) {
    init();
}

void Cursor::draw() {
    if (bi::mouseInput().xPos != -1)
        bi::ioManager().renderer->drawTexture(mouseInput().getPosition() + offset, size, color, cursorTextureId, 0, currentTextCoord);
}

