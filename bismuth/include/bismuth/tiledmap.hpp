#pragma once
#include "bismuth/logging.hpp"
#include <bismuth/tile.hpp>
#include <map>
#include <string>
#include <tmxlite/Map.hpp>
#include <tmxlite/Object.hpp>
#include <tmxlite/Tileset.hpp>
#include <vector>

namespace bi {

class TiledCustomProperty {
private:
    std::string stringValue;
    bool boolValue;
    float floatValue;
    int intValue;
    glm::vec4 colorValue;
    bool gotValue = false;

public:
    TiledCustomProperty() { }

    bool exists()
    {
        return gotValue;
    }

    void setBoolValue(bool value)
    {
        gotValue = true;
        this->boolValue = value;
    }

    bool getBoolValue()
    {
        return boolValue;
    }

    void setStringValue(std::string value)
    {
        gotValue = true;
        this->stringValue = value;
    }

    std::string getStringValue()
    {
        return stringValue;
    }

    void setFloatValue(float value)
    {
        gotValue = true;
        this->floatValue = value;
    }

    float getFloatValue()
    {
        return floatValue;
    }

    void setIntValue(int value)
    {
        gotValue = true;
        this->intValue = value;
    }

    int getIntValue()
    {
        return intValue;
    }

    void setColorValue(glm::vec4 value)
    {
        gotValue = true;
        this->colorValue = value;
    }

    glm::vec4 getColorValue()
    {
        return colorValue;
    }
};

class TiledObject {

private:
    std::map<std::string, TiledCustomProperty> metadata;

    TiledCustomProperty empty;
    void addCustomProperty(std::string key, TiledCustomProperty value)
    {
        this->metadata.emplace(key, value);
    }

public:
    tmx::Object object;
    Tile tile;
    TiledObject(tmx::Object object, Tile tile)
        : object(object)
        , tile(tile)
    {
        for (auto& prop : object.getProperties()) {
            TiledCustomProperty customProperty;
            switch (prop.getType()) {
            case tmx::Property::Type::Boolean:
                customProperty.setBoolValue(prop.getBoolValue());
                this->addCustomProperty(prop.getName(), customProperty);
                break;
            case tmx::Property::Type::Float:
                customProperty.setFloatValue(prop.getFloatValue());
                this->addCustomProperty(prop.getName(), customProperty);
                break;
            case tmx::Property::Type::Int:
                customProperty.setIntValue(prop.getIntValue());
                this->addCustomProperty(prop.getName(), customProperty);
                break;

            case tmx::Property::Type::String:
                customProperty.setStringValue(prop.getStringValue());
                this->addCustomProperty(prop.getName(), customProperty);
                break;

            case tmx::Property::Type::Colour:
                customProperty.setColorValue({ prop.getColourValue().r, prop.getColourValue().g, prop.getColourValue().b, prop.getColourValue().a });
                this->addCustomProperty(prop.getName(), customProperty);
                break;
            case tmx::Property::Type::File:
            case tmx::Property::Type::Undef:
                bi::log("Bismuth doesn't currently support File and Object");
            }
        }
    }

    bool setCustomProperty(std::string key, std::string value)
    {
        if (this->metadata.count(key) > 0) {
            this->metadata.at(key).setStringValue(value);
            return true;
        }
        return false;
    }

    bool setCustomProperty(std::string key, bool value)
    {
        if (this->metadata.count(key) > 0) {
            this->metadata.at(key).setBoolValue(value);
            return true;
        }
        return false;
    }

    bool setCustomProperty(std::string key, float value)
    {
        if (this->metadata.count(key) > 0) {
            this->metadata.at(key).setFloatValue(value);
            return true;
        }
        return false;
    }

    bool setCustomProperty(std::string key, int value)
    {
        if (this->metadata.count(key) > 0) {
            this->metadata.at(key).setIntValue(value);
            return true;
        }
        return false;
    }
    bool setCustomProperty(std::string key, glm::vec4 value)
    {
        if (this->metadata.count(key) > 0) {
            this->metadata.at(key).setColorValue(value);
            return true;
        }
        return false;
    }

    TiledCustomProperty& getCustomProperty(std::string key)
    {
        if (metadata.count(key) > 0) {
            return this->metadata.at(key);
        } else {
            bi::log("FaILED GETTING value metadata");
        }
        return this->empty;
    }
};
class TiledMap {
public:
    TiledMap(std::string filepath)
        : filePath(filepath)
    {
        loadMap();
    }

    ~TiledMap();

    std::vector<Tile>& getTiles(unsigned int layerNumber);
    std::vector<TiledObject>& getObjects(unsigned int objectNumber);
    void loadMap();

    glm::vec2 tileCount;
    glm::vec2 tileSize;

private:
    std::string filePath;
    //layers
    std::map<int, std::vector<Tile>> tiles;
    std::map<int, tmx::Tileset> tilesets;
    std::map<int, int> textureIds;
    std::map<int, std::vector<TiledObject>> objects;
    int tilesetIndexOfTile(unsigned int tileId);
};
}
