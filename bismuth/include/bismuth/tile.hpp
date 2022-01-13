#pragma once
#include <array>
#include <glm/glm.hpp>
namespace bi {
    class Tile {
        public:
            Tile(int tileId, int textureId, glm::vec2 imagesize, glm::vec2 pos, glm::vec2 tilesize) :
                id(tileId), texId(textureId), imageSize(imagesize), position(pos), tileSize(tilesize) {
                    setup();
                }
            ~Tile();
            void animate();
            std::array<glm::vec2, 4> getTexCoords();
            glm::vec2 getPosition();
            void setPosition(glm::vec2 pos);
            unsigned int getTextureId();
            unsigned int getId();
            glm::vec2 getTileSize();
            glm::vec2 getTileCell();
            bool isEmpty();

        private:
            std::array<glm::vec2, 4> texCoords;
            void setup();
            unsigned int id;
            int texId;
            glm::vec2 imageSize;
            glm::vec2 position;
            glm::vec2 tileSize;
    };
}
