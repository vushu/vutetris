#include "game.hpp"
#include "bismuth/keylistener.hpp"
#include "scenes/level1.hpp"
#include "scenes/main_menu.hpp"

Game::~Game() {}

void Game::init() {
    getAudioManager().init();
    getAudioManager().start();
    getSceneManager().addScene("MainMenu", std::make_unique<scenes::MainMenu>(), true);
    getSceneManager().addScene("Level1", std::make_unique<scenes::Level1>());
}

void Game::processInput(float dt) {
    if (bi::keyInput().isKeyPressed(bi::Key::ESCAPE))  {
        this->getWindow().close();
    }
}

void Game::update(float dt) {

}

void Game::render(float dt) {

}
