#pragma once
#include "texture.hpp"
#include<memory>
namespace bi {
    class Framebuffer{
        public:
            // constructors, asssignment, destructor
            Framebuffer();
            ~Framebuffer();
            void init(int width, int height);
            void bind();
            void unbind();
            unsigned int textureId = 0;
        private:
            unsigned int fboId;
            std::unique_ptr<Texture> texture;

    };
}
