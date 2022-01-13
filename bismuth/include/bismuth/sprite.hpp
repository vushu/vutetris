#pragma once
#include <glm/glm.hpp>
#include "texture.hpp"
#include <vector>
#include <memory>
namespace bi {
    class Sprite {
        public:
            // constructors, asssignment, destructor
            Sprite(std::shared_ptr<Texture> texture);
            Sprite(std::string filepath);
            Sprite();
            ~Sprite();

            int getTextureId();
            void setTexture(std::shared_ptr<Texture> texture);
            void setTexCoords(std::vector<glm::vec2> texCoords);
            std::vector<glm::vec2> getTexCoords();
            std::shared_ptr<Texture> getTexture();
            std::string getTextureFilePath();

        private:
            std::shared_ptr<Texture> texture;
            void construct();
            float width, height;
            std::vector<glm::vec2> texCoords;
            std::string filepath = "";
    };
}
