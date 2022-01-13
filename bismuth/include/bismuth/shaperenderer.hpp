#pragma once
#include "glm/fwd.hpp"
#include "primitives.hpp"
#include <glad/glad.h>
#include "shader.hpp"
#include "camera.hpp"
namespace bi {
    class ShapeRenderer{

        struct ShaperRenderData {
            GLuint quadVA = 0;
            GLuint quadVB = 0;
            GLuint quadIB = 0;

            SimpleVertex* vertexBuffer = nullptr;
            SimpleVertex* currentLocationPtr = nullptr;
            int vertexCounter = 0;
        };

        public:
            // constructors, asssignment, destructor
            ShapeRenderer(Camera& cam) : camera(cam) {}
            ~ShapeRenderer();

            void init();
            ShapeRenderer& drawLine(glm::vec2 posFrom, glm::vec2 posTo, glm::vec4 color, float angle = 0.0f, bool centerShown = false);
            ShapeRenderer& drawRect(glm::vec2 position, glm::vec2 size, glm::vec4 color, float angle = 0.0f, bool centerShown = false);
            ShapeRenderer& drawPolygon(glm::vec2 centerPos, float radius, int segments, glm::vec4 color, float angle, bool centerShown = false);
            ShapeRenderer& drawGrid(glm::vec2 tileSize, glm::vec2 tileCount, glm::vec2 offset = glm::vec2{0.0f,0.0f}, glm::vec4 color = glm::vec4{0.5f,0.4f,0.5f,0.8f});
            ShapeRenderer& setLineWidth(float lineWidth);
            ShapeRenderer& fill();
            void beginBatch();
            void endBatch();
            void flush();
            void endFlushBegin();

        private:
            Camera& camera;
            Shader shader{"resources/assets/shaders/shape.glsl"};
            ShaperRenderData renderData;
            int maxVertexCount = 2000;
            void setVertex(glm::vec2 position, glm::vec4);
            void checkVertexLimit();
            glm::vec2 rotatePoint(const glm::vec2& pos, float angle);
            void drawPoint(glm::vec2 point, float angle = 0.0f);

            //default values
            float lineWidth = 1.2f;
            bool filled = false;
            void resetToDefault();

    };
}
