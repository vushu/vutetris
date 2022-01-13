#pragma once
#include <bismuth/sprite.hpp>
#include <bismuth/primitives.hpp>
#include <glm/glm.hpp>
namespace bi  {
    class SpriteRenderer
    {
        public:
            SpriteRenderer(std::unique_ptr<Sprite> sprite);
            ~SpriteRenderer();

            glm::vec4 color;
            bool isDirty = true;
            void setSprite(Sprite sprite);
            void setColor(glm::vec4 color);
            void setPosition(glm::vec2 position);
            void setScale(glm::vec2 scale);
            void setTextureCoords(std::vector<glm::vec2> coords);
            std::string getTextureFilePath();

            std::shared_ptr<Texture> getTexture();
            std::vector<glm::vec2> getTexCoords();
            void setClean();
            void initTexture();
            void setRotation(float radian);
            glm::vec2 position;
            glm::vec2 scale;
            float angle = 0;
            void updateBuffer(QuadVertex* quadPtr);

        private:
            std::unique_ptr<Sprite> mSprite;
            glm::vec2 rotatePoint(const glm::vec2& pos, float angle);
    };
}
