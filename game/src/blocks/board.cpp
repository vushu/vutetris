#include "board.hpp"
#include "bismuth/iomanager.hpp"
#include "bismuth/logging.hpp"
#include "block.hpp"
using namespace blocks;

Board::Board() { init(); }

Board::~Board() { }

void Board::drawGrid()
{
    bi::ioManager().shaperenderer->drawGrid({ tilesize, tilesize }, { 10, 20 },
        this->position);
    bi::ioManager().shaperenderer->endFlushBegin();
}

void Board::init()
{
    centerPosition();
    glm::mat4 iCoords = { { 1, 0, 0, 0 }, { 1, 0, 0, 0 }, { 1, 0, 0, 0 }, { 1, 0, 0, 0 } };

    tetrominoes.emplace("I", Block { { 0, 0 }, bi::color::fromRGB(0, 255, 255, 255), iCoords });
    glm::mat4 oCoords = { { 1, 1, 0, 0 }, { 1, 1, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };
    tetrominoes.emplace("O", Block { { 0, 0 }, bi::color::SOFT_YELLOW, oCoords });

    glm::mat4 tCoords = { { 1, 1, 1, 0 }, { 0, 1, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };

    tetrominoes.emplace("T", Block { { 0, 0 }, bi::color::SOFT_MAGENTA, tCoords });
    glm::mat4 sCoords = { { 0, 1, 1, 0 }, { 1, 1, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };

    tetrominoes.emplace("S", Block { { 0, 0 }, bi::color::SOFT_GREEN, sCoords });
    glm::mat4 zCoords = { { 1, 1, 0, 0 }, { 0, 1, 1, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };

    tetrominoes.emplace("Z", Block { { 0, 0 }, bi::color::SOFT_RED, zCoords });
    glm::mat4 jCoords = { { 0, 1, 0, 0 }, { 0, 1, 0, 0 }, { 1, 1, 0, 0 }, { 0, 0, 0, 0 } };
    tetrominoes.emplace("J", Block { { 0, 0 }, bi::color::SOFT_BLUE, jCoords });
    glm::mat4 lCoords = { { 1, 0, 0, 0 }, { 1, 0, 0, 0 }, { 1, 1, 0, 0 }, { 0, 0, 0, 0 } };

    tetrominoes.emplace("L", Block { { 0, 0 }, bi::color::SOFT_ORANGE, lCoords });
    this->setupDebugButton();
}

void Board::centerPosition()
{
    this->position = {
        bi::ioManager().camera->width * 0.5f - (10 * tilesize * 0.5),
        bi::ioManager().camera->height * 0.5 - (20 * tilesize * 0.5)
    };
}
void Board::print(std::string letter) { tetrominoes.at(letter).draw(); }

void Board::setCurrentBlock(std::string letter) { this->currentBlock = letter; }

void Board::setupDebugButton()
{
    int debugButtonWidth = 140;
    this->leftDebugButton = std::make_shared<bi::gui::GuiButton>();
    this->leftDebugButton->setSize({ debugButtonWidth, 50 });
    this->leftDebugButton->setOffset({ 20, 0 });
    this->leftDebugButton->setText("Left");
    this->leftDebugButton->positionCenterLeftTo(
        { 0, 0 }, { bi::ioManager().camera->width, bi::ioManager().camera->height });

    this->leftDebugButton->onLeftMousePressed([&](bi::gui::GuiButton& button) {
        tetrominoes.at(currentBlock).incrementTilePos({ -1, 0 });
    });

    this->rightDebugButton = std::make_shared<bi::gui::GuiButton>();
    this->rightDebugButton->setSize({ debugButtonWidth, 50 });
    this->rightDebugButton->setOffset({ -20, 0 });
    this->rightDebugButton->setText("Right");
    this->rightDebugButton->positionCenterRightTo(
        { 0, 0 }, { bi::ioManager().camera->width, bi::ioManager().camera->height });

    this->rightDebugButton->onLeftMousePressed([&](bi::gui::GuiButton& button) {
        tetrominoes.at(currentBlock).incrementTilePos({ 1, 0 });
    });

    this->upDebugButton = std::make_shared<bi::gui::GuiButton>();
    this->upDebugButton->setSize({ debugButtonWidth, 50 });
    this->upDebugButton->setOffset({ 0, 20 });
    this->upDebugButton->setText("Up");
    this->upDebugButton->positionTopCenterTo(
        { 0, 0 }, { bi::ioManager().camera->width, bi::ioManager().camera->height });

    this->upDebugButton->onLeftMousePressed([&](bi::gui::GuiButton& button) {
        tetrominoes.at(currentBlock).incrementTilePos({ 0, -1 });
    });

    this->downDebugButton = std::make_shared<bi::gui::GuiButton>();
    this->downDebugButton->setSize({ debugButtonWidth, 50 });
    this->downDebugButton->setOffset({ 0, -20 });
    this->downDebugButton->setText("Down");
    this->downDebugButton->positionBottomCenterTo({ 0, 0 }, { bi::ioManager().camera->width, bi::ioManager().camera->height });

    this->downDebugButton->onLeftMousePressed([&](bi::gui::GuiButton& button) {
        tetrominoes.at(currentBlock).incrementTilePos({ 0, 1 });
    });

    this->rotateRightDebugButton = std::make_shared<bi::gui::GuiButton>();
    this->rotateRightDebugButton->setSize({ debugButtonWidth, 50 });
    this->rotateRightDebugButton->setOffset({ 200, 0 });
    this->rotateRightDebugButton->setText("O >");
    this->rotateRightDebugButton->positionCenterTo({ 0, 0 }, { bi::ioManager().camera->width, bi::ioManager().camera->height });

    this->rotateRightDebugButton->onLeftMousePressed([&](bi::gui::GuiButton& button) {
    });
    this->rotateLeftDebugButton = std::make_shared<bi::gui::GuiButton>();
    this->rotateLeftDebugButton->setSize({ debugButtonWidth, 50 });
    this->rotateLeftDebugButton->setOffset({ -200, 0 });
    this->rotateLeftDebugButton->setText("< O");
    this->rotateLeftDebugButton->positionCenterTo({ 0, 0 }, { bi::ioManager().camera->width, bi::ioManager().camera->height });

    this->rotateLeftDebugButton->onLeftMousePressed([&](bi::gui::GuiButton& button) {
        tetrominoes.at(currentBlock).rotateLeft();
    });
}

void Board::drawDebugButtons()
{
    this->leftDebugButton->draw();
    this->rightDebugButton->draw();
    this->upDebugButton->draw();
    this->downDebugButton->draw();
    this->rotateLeftDebugButton->draw();
    this->rotateRightDebugButton->draw();
}

void Board::processInput()
{
    this->leftDebugButton->processInput();
    this->rightDebugButton->processInput();
    this->upDebugButton->processInput();
    this->downDebugButton->processInput();
    this->rotateLeftDebugButton->processInput();
    this->rotateRightDebugButton->processInput();
}

bool Board::isColliding() { return false; }

void Board::update()
{
    tetrominoes.at(currentBlock).setOffset(position);
}

void Board::draw()
{
    tetrominoes.at(currentBlock).draw();
    drawDebugButtons();
    drawGrid();
}
