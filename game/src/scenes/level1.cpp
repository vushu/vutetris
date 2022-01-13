#include "level1.hpp"
using namespace scenes;

Level1::Level1() {}

Level1::~Level1() {}

void Level1::init() {
    board.print("L");
}

void Level1::start() {
    getAudioManager().playSound("resources/assets/audio/game.mp3");
}

void Level1::processInput(float dt) {
    board.processInput();
}

void Level1::update(float dt) {
    board.update();
}

void Level1::render(float dt) {
    getRenderer().clear();
    board.draw();
    getCursor().draw();

    getRenderer().endFlushBegin();

}

void Level1::close() {}

