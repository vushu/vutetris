#include <bismuth/iomanager.hpp>
#include <bismuth/tiledmap.hpp>
#include <bismuth/logging.hpp>
#include <stdexcept>
#include <tmxlite/TileLayer.hpp>
using namespace bi;

TiledMap::~TiledMap() { }

std::vector<bi::Tile>& TiledMap::getTiles(unsigned int layerNumber) {
    if (tiles.count(layerNumber) > 0)
        return tiles.at(layerNumber);
    else {
        throw std::runtime_error("Layer number " + std::to_string(layerNumber) + " doesn't exists!");
    }
}

std::vector<bi::TiledObject>& TiledMap::getObjects(unsigned int objectNumber) {
    if (objects.count(objectNumber) > 0)
        return this->objects.at(objectNumber);
    throw std::runtime_error("Layer number " + std::to_string(objectNumber) + " doesn't exists!");
}


//std::vector<bi::TiledObject>& TiledMap::getObjects(unsigned int objectNumber) {
//if (objects.count(objectNumber) > 0)
//return this->objects.at(objectNumber);
//throw std::runtime_error("Layer number " + std::to_string(objectNumber) + " doesn't exists!");
//}

void TiledMap::loadMap() {
    tmx::Map map;
    if (map.load(filePath)) {
        tileSize = { map.getTileSize().x, map.getTileSize().y };
        tileCount = { map.getTileCount().x, map.getTileCount().y };
        const auto& ts = map.getTilesets();

        for (unsigned int i = 0; i < ts.size(); i++) {
            this->tilesets.emplace(i, ts[i]);
            this->textureIds.emplace(i, bi::ioManager().assetmanager->loadTexture(ts[i].getImagePath()));
        }

        int tilePosX = 0;
        int tilePosY = 0;
        int tileCount = 0;
        int objectCount = 0;
        int tileSetIdx = -1;
        int tileSetIdxForObject = -1;
        glm::vec2 pos;

        for (const auto& layer : map.getLayers()) {

            if (layer->getType() == tmx::Layer::Type::Object) {
                std::vector<bi::TiledObject> objectList;
                const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();

                for (unsigned int i = 0; i < objectLayer.getObjects().size(); i++) {
                    const auto& o = objectLayer.getObjects()[i];

                    tilePosX = o.getPosition().x;
                    tilePosY = o.getPosition().y;

                    tileSetIdxForObject = tilesetIndexOfTile(o.getTileID());
                    const auto &foundTileSet = this->tilesets.at(tileSetIdxForObject);

                    //bi::log("TileIdX", tileSetIdxForObject);

                    const auto &imgSize = this->tilesets.at(tileSetIdxForObject).getImageSize();

                    // position.y - tileSize.y, since it looks like tiled uses bottom left as origin
                    bi::Tile tile(o.getTileID() - foundTileSet.getFirstGID(), textureIds.at(tileSetIdxForObject), {imgSize.x, imgSize.y}, { o.getPosition().x, o.getPosition().y - tileSize.y }, { tileSize.x, tileSize.y });

                    TiledObject obj{o, tile};

                    objectList.push_back(std::move(obj));

                }
                objects.emplace(objectCount, std::move(objectList));
                objectCount++;
                //bi::log("Done with objects layers: ", objectCount);
            }

            else if (layer->getType() == tmx::Layer::Type::Tile) {
                std::vector<bi::Tile> tileList;
                const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();

                for (unsigned int i = 0; i < tileLayer.getTiles().size(); i++) {
                    const auto& t = tileLayer.getTiles()[i];

                    tilePosX = i % tileLayer.getSize().x;
                    tilePosY = (int) (i / tileLayer.getSize().x);

                    pos = {tilePosX * tileSize.x, tilePosY * tileSize.y};

                    tileSetIdx = tilesetIndexOfTile(t.ID);

                    const auto &foundTileSet = this->tilesets.at(tileSetIdx);
                    const auto &imgSize = foundTileSet.getImageSize();

                    bi::Tile tile(t.ID - foundTileSet.getFirstGID(), textureIds.at(tileSetIdx), {imgSize.x, imgSize.y}, pos, {tileSize.x, tileSize.y});

                    tileList.push_back(tile);
                }
                tiles.emplace(tileCount, std::move(tileList));
                tileCount++;
            }
        }

    }
}

int TiledMap::tilesetIndexOfTile(unsigned int tileId) {
    int tilesetIndex = 0;
    for(unsigned int i = 0; i < tilesets.size(); i++) {
        if (tilesets.at(i).hasTile(tileId)) {
            tilesetIndex = i;
            break;
        }
    }
    return tilesetIndex;
}


