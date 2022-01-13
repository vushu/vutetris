#include "bismuth/iomanager.hpp"
#include "bismuth/shaperenderer.hpp"
#include <bismuth/tiledmanager.hpp>
using namespace bi;

TiledManager::TiledManager() { }
TiledManager::~TiledManager()
{
    bi::log("TiledManager destroyed");
}

TiledMap& TiledManager::loadTileMap(std::string filepath)
{
    if (tiledMaps.count(filepath) > 0)
        return *this->tiledMaps.at(filepath);
    else {
        this->tiledMaps.emplace(filepath, std::make_unique<TiledMap>(filepath));
    }
    return *this->tiledMaps.at(filepath);
}

void TiledManager::draw(std::string filepath, int layerNumber)
{
    for (auto& tile : loadTileMap(filepath).getTiles(layerNumber)) {
        bi::ioManager().renderer->drawTexture(tile.getPosition(), tile.getTileSize(), { 1, 1, 1, 1 }, tile.getTextureId(), 0, tile.getTexCoords());
    }
}

void TiledManager::drawGridVG(std::string filepath)
{
    const TiledMap& map = loadTileMap(filepath);


    for (int i = 0; i <= map.tileCount.x; i++) {

        //bi::ioManager().shaperenderer->drawLine({ i * map.tileSize.x, 0 }, { i * map.tileSize.x, map.tileCount.y * map.tileSize.x }, color);
    }

    for (int i = 0; i <= map.tileCount.y; i++) {
        //bi::ioManager().shaperenderer->drawLine({ 0, i * map.tileSize.y }, { map.tileCount.x * map.tileSize.y, i * map.tileSize.y }, color);
    }

}

void TiledManager::drawGrid(std::string filepath, glm::vec4 color)
{

    const TiledMap& map = loadTileMap(filepath);

    for (int i = 0; i <= map.tileCount.x; i++) {
        bi::ioManager().shaperenderer->drawLine({ i * map.tileSize.x, 0 }, { i * map.tileSize.x, map.tileCount.y * map.tileSize.x }, color);
    }

    for (int i = 0; i <= map.tileCount.y; i++) {
        bi::ioManager().shaperenderer->drawLine({ 0, i * map.tileSize.y }, { map.tileCount.x * map.tileSize.y, i * map.tileSize.y }, color);
    }
}
