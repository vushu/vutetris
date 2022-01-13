#pragma once
#include <string>
#include <glm/glm.hpp>
#include <array>
namespace bi {
    class Texture {
        public:
            Texture (std::string filepath);
            Texture (int w, int h) : width(w), height(h) {

            }
            Texture ();
            ~Texture ();
            void init();
            int width = 0, height = 0;
            void bind();
            void unbind();
            unsigned int textureId;
            std::string filepath;
            std::array<glm::vec2,4> getTexCoords(int tileNumber, glm::vec2 tilesize);

        private:




    };
}
