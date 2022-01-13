#include "main_menu.hpp"
#include "bismuth/color.hpp"
#include "bismuth/gui/gui_button.hpp"
#include "bismuth/gui/gui_window.hpp"
#include "bismuth/keylistener.hpp"
#include "bismuth/logging.hpp"
#include "bismuth/mouselistener.hpp"
#include <memory>
using namespace scenes;

MainMenu::MainMenu() {}

MainMenu::~MainMenu() {}

void MainMenu::initWindow() {
    this->quitBtn = std::make_shared<bi::gui::GuiButton>();
    this->quitBtn->setSize({400, 60});
    this->quitBtn->setText("QUIT");


    this->fullscreenBtn = std::make_shared<bi::gui::GuiButton>();
    this->fullscreenBtn->setSize({400, 60});
    this->fullscreenBtn->setText("FULLSCREEN");

    this->startBtn = std::make_shared<bi::gui::GuiButton>();
    this->startBtn->setSize({400, 60});
    this->startBtn->setText("START");
    this->windowMenu = std::make_unique<bi::gui::GuiWindow>();
    this->windowMenu->setSize({500, 250});
    this->windowMenu->setBackgroundColor(bi::color::CORNFLOWER_BLUE);

    this->windowMenu->add(startBtn, bi::gui::TOP_CENTER);
    this->windowMenu->add(fullscreenBtn, bi::gui::CENTER);
    this->windowMenu->add(quitBtn, bi::gui::BOTTOM_CENTER);

    this->windowMenu->positionCenterTo({0,0}, getWindow().size());

    startBtn->onLeftMousePressed([&](bi::gui::GuiButton& button){
            getAudioManager().playSound("resources/assets/audio/pling.wav");
            nextScene = "Level1";
            });

    startBtn->onMouseOver([&](bi::gui::GuiButton& button){
            button.setBackgroundColor({0,0.4,0.2,0.5f});
            getAudioManager().playSound(mouseOverSoundFile);
            });
    fullscreenBtn->onMouseOver([&](bi::gui::GuiButton& button){
            button.setBackgroundColor({0.0,0.6,0.8,0.5f});
            getAudioManager().playSound(mouseOverSoundFile);
            });
    quitBtn->onLeftMousePressed([&](bi::gui::GuiButton& button){
            button.setBackgroundColor({0.0,0.0,0.8,0.5f});
            getAudioManager().playSound("resources/assets/audio/explosion.wav");
            counter.start();
            });


    quitBtn->onMouseOver([&](bi::gui::GuiButton& button){
            button.setBackgroundColor({0.0,0.0,0.8,0.5f});
            getAudioManager().playSound(mouseOverSoundFile);
            });

    fullscreenBtn->onLeftMousePressed([&](bi::gui::GuiButton& button){
            if (!fullscreen) {
            getWindow().fullscreen();
            this->fullscreenBtn->setText("WINDOW");
            fullscreen = true;
            }
            else{
            getWindow().windowed(960,540);
            this->fullscreenBtn->setText("FULLSCREEN");
            fullscreen = false;
            }

            });
    counter.onCount([&](int count){
            bi::log("Count is", count);
            getWindow().close();
            });

    auto& s = getAudioManager().getSound("resources/assets/audio/pling.wav");
    s.setVolume(0.1f);


}

void MainMenu::init() {
    bi::mouseInput().hideCursor();
    initWindow();
}

void MainMenu::start() {}

void MainMenu::processInput(float dt) {
    if (bi::keyInput().isKeyPressed(bi::Key::F)) {
        getWindow().fullscreen();
    }
    if (bi::keyInput().isKeyPressed(bi::Key::W)) {
        getWindow().windowed(960, 540);
    }


}

void MainMenu::update(float dt) {
    counter.updateIncrement();
    this->windowMenu->processInput();
}

void MainMenu::render(float dt) {
    getRenderer().clear();
    windowMenu->draw();
    getCursor().draw();
    getRenderer().endFlushBegin();
}

void MainMenu::close() {
    getCursor().setMouseOver(false);
}

