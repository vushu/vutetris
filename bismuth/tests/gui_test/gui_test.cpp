#include "gui_test.hpp"
#include <bismuth/bismuth.hpp>
#include <catch2/catch.hpp>
#include "bismuth/keyboard.hpp"
#include "scenes/gui_window_scene.hpp"
#include <iostream>
#include <memory>
#include <string>

GuiTest::~GuiTest() {
}

void GuiTest::setupGuiEvents() {

    bismuthCounter.onCount([&](int count){
        switch (count) {
        case 1:
            bismuthLabel->setVisible(true);
            bismuthLabel->setText("B");
            getAudioManager().playSound(explosionSoundFile);
            break;
        case 2:
            bismuthLabel->setText("BI");
            getAudioManager().playSound(explosionSoundFile);
            break;
        case 3:
            bismuthLabel->setText("BIS");
            getAudioManager().playSound(explosionSoundFile);
            break;
        case 4:
            bismuthLabel->setText("BISM");
            getAudioManager().playSound(explosionSoundFile);
            break;
        case 5:
            bismuthLabel->setText("BISMU");
            getAudioManager().playSound(explosionSoundFile);
            break;
        case 6:
            bismuthLabel->setText("BISMUT");
            getAudioManager().playSound(explosionSoundFile);
            break;
        case 7:
            bismuthLabel->setText("BISMUTH");
            getAudioManager().playSound(explosionSoundFile);
            break;
        case 8:
            getAudioManager().playSound(bismuthSoundFile);
            break;
        case 10:
            bismuthLabel->setVisible(false);
            getSceneManager().setScene("GuiWindowScene");
            break;
        }
    });

}
void GuiTest::init() {

    getSceneManager().addScene("GuiWindowScene", std::make_unique<scenes::GuiWindowScene>());

    bi::mouseInput().hideCursor();

    getAudioManager().init();
    getAudioManager().start();
    getAudioManager().getSound(explosionSoundFile).setVolume(0.5f);

    bismuthLabel = std::make_shared<bi::gui::GuiLabel>();

    bismuthLabel->fontScale = 1.5f;
    bismuthLabel->setText("BISMUTH");
    bismuthLabel->setOffset({0, -10});
    bismuthLabel->setVisible(false);
    bismuthLabel->positionCenterTo({0,0}, getWindow().size());

    setupGuiEvents();
    bismuthCounter.start();

}

void GuiTest::update(float dt) {
    bismuthCounter.updateIncrement();
}

void GuiTest::processInput(float dt) {

    if (bi::keyInput().isKeyPressed(bi::Key::ESCAPE)){
        getWindow().close();
    }
}

void GuiTest::render(float dt) {

    getRenderer().clear();

    bismuthLabel->draw();

    getCursor().draw();

    getRenderer().endFlushBegin();

}
