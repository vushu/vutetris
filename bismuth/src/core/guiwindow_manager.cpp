#include <bismuth/gui/guiwindow_manager.hpp>
using namespace bi::gui;

GuiWindowManager::~GuiWindowManager() { }

GuiWindowManager::GuiWindowManager() {

}

GuiWindowManager& GuiWindowManager::add(std::unique_ptr<GuiWindow> window) {
    this->windows.push_back(std::move(window));
    return *this;
}

void GuiWindowManager::processInput() {

}

void GuiWindowManager::update() {

}

void GuiWindowManager::draw() {
}





