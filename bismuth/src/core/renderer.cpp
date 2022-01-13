#include <bismuth/spriterenderer.hpp>
#include <array>
#include <bismuth/renderer.hpp>
#include <cstring>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <bismuth/logging.hpp>
#include "bismuth/color.hpp"
#include "bismuth/glhelper.hpp"
#include "bismuth/primitives.hpp"
#include "glm/fwd.hpp"
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace bi;

void checkGLError()
{
    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR){
        std::cout << err;
        throw std::runtime_error("ERROR");
    }
}

void Renderer::init()  {

    //glhelper::createFrameBuffer();
    this->shader.compile();

    s_renderData.quadBuffer = new QuadVertex[maxVertexCount];

    glGenVertexArrays(1, &s_renderData.quadVA);
    glBindVertexArray(s_renderData.quadVA);

    glGenBuffers(1, &s_renderData.quadVB);
    glBindBuffer(GL_ARRAY_BUFFER, s_renderData.quadVB);
    //reserving buffer of maxVertexCount
    glBufferData(GL_ARRAY_BUFFER, maxVertexCount * sizeof(QuadVertex) , nullptr, GL_DYNAMIC_DRAW);

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        // Failed
        glDeleteBuffers(1, &s_renderData.quadVB);
        throw std::runtime_error("Failed to bind buffer");
        //vbo = 0;
    }
    // Enabling attributes
    // position
    //
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const GLvoid *) offsetof(QuadVertex, position));
    //color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const GLvoid *) offsetof(QuadVertex, color));
    //texcoords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex),  (const GLvoid *) offsetof(QuadVertex, texcoords));
    //texId
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const GLvoid *) offsetof(QuadVertex, texId));
    //type
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const GLvoid *) offsetof(QuadVertex, type));

    //disable for good measure
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glDisableVertexAttribArray(4);


    //Create indices
    uint32_t indices[maxIndexCount];
    uint32_t offset = 0;

    for (unsigned int i = 0; i < maxIndexCount; i += 6) {

        /*
           indices[i + 0] = 0 + offset;
           indices[i + 1] = 1 + offset;
           indices[i + 2] = 3 + offset;

           indices[i + 3] = 1 + offset;
           indices[i + 4] = 2 + offset;
           indices[i + 5] = 3 + offset;
           */


        indices[i + 0] = 3 + offset;
        indices[i + 1] = 2 + offset;
        indices[i + 2] = 0 + offset;

        indices[i + 3] = 0 + offset;
        indices[i + 4] = 2 + offset;
        indices[i + 5] = 1 + offset;

        offset += 4;
    }

    glGenBuffers(1, &s_renderData.quadIB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_renderData.quadIB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //Done generating
    //Batch data
    log("Batch data initialized");

    GLenum erre = glGetError();
    if (erre != GL_NO_ERROR) {
        log("ERROR: !!" + std::to_string(erre));
    }
    // remember to close very important or other attributes made by others is overwritting it
    glBindVertexArray(0);
    beginBatch();

}



void Renderer::beginBatch() {

    //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    //log("*************** begin batch ******************");
    s_renderData.currentLocationPtr = s_renderData.quadBuffer;
    //s_renderData.indexCount = 0;

}

void Renderer::endBatch() {

    GLsizeiptr size = (uint8_t*) this->s_renderData.currentLocationPtr - (uint8_t*) this->s_renderData.quadBuffer;
    glBindBuffer(GL_ARRAY_BUFFER, s_renderData.quadVB);
    //log("Size of buffer:" + std::to_string(size));
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, s_renderData.quadBuffer);
    //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
}

glm::vec2 Renderer::rotatePoint(const glm::vec2& pos, float angle) {
    glm::vec2 newPos;
    newPos.x = pos.x * cos(angle) - pos.y * sin(angle);
    newPos.y = pos.x * sin(angle) + pos.y * cos(angle);
    return newPos;
}

void Renderer::endFlushBegin(){
    endBatch();
    flush();
    beginBatch();
}

void Renderer::drawTexture(glm::vec2 pos, glm::vec2 size, glm::vec4 color, int texId, float angle, std::array<glm::vec2, 4> texcoords) {

    reevaluateBatchSpace();
    float textureIndex = getTextureIndex(texId);

    setQuadVertices(s_renderData.currentLocationPtr, pos, size, color, textureIndex, angle, texcoords);
    incrementDrawCounters();
}

std::array<glm::vec2, 4> Renderer::getCorners(glm::vec2 position, glm::vec2 size, float angle) {
    glm::vec2 halfDims(size * 0.5f);

    glm::vec2 tl(-halfDims.x, halfDims.y);
    glm::vec2 bl(-halfDims.x, -halfDims.y);
    glm::vec2 br(halfDims.x, -halfDims.y);
    glm::vec2 tr(halfDims.x, halfDims.y);

    glm::vec2 topLeft, botLeft, botRight, topRight;

    if (angle != 0) {
        topLeft = rotatePoint(tl, angle) + halfDims + position;
        botLeft = rotatePoint(bl, angle) + halfDims + position;
        botRight = rotatePoint(br, angle) + halfDims + position;
        topRight = rotatePoint(tr, angle) + halfDims + position;
    }

    else {
        topLeft = position;
        botLeft = {position.x, position.y + size.y};
        botRight = {position.x + size.x, position.y + size.y };
        topRight = {position.x + size.x, position.y};
    }


    return {botRight, topRight, topLeft, botLeft};
}

void Renderer::setQuadVertex(QuadVertex*& quadVertex, glm::vec2 position, glm::vec2 size, glm::vec2 texCoord, glm::vec4 color, float texId, float type) {
    quadVertex->position = { position, 0.0f};
    quadVertex->color = color::fromRGB(color);
    quadVertex->texcoords = texCoord;
    quadVertex->texId = texId;
    quadVertex->type = type;
    quadVertex++;
}

void Renderer::setQuadVertices(QuadVertex*& quadVertex, glm::vec2 position, glm::vec2 size, glm::vec4 color, float texId, float angle, std::array<glm::vec2, 4> texcoords, float type) {
    std::array<glm::vec2,4> corners = getCorners(position, size, angle);

    setQuadVertex(quadVertex, corners.at(0), size, texcoords.at(0), color, texId, type);
    setQuadVertex(quadVertex, corners.at(1), size, texcoords.at(1), color, texId, type);
    setQuadVertex(quadVertex, corners.at(2), size, texcoords.at(2), color, texId, type);
    setQuadVertex(quadVertex, corners.at(3), size, texcoords.at(3), color, texId, type);
}


Renderer& Renderer::drawQuad(glm::vec2 pos, glm::vec2 size, glm::vec4 color, float angle) {
    reevaluateBatchSpace();
    setQuadVertices(s_renderData.currentLocationPtr, pos, size, color, 0.0f, angle);
    incrementDrawCounters();
    return *this;
}

void Renderer::flush() {

    shader.use();
    shader.uploadUniformMat4("uMvp", camera.projectionMatrix * camera.getViewMatrix());


    for (unsigned int i = 0; i < s_renderData.textureSlotsIndex; i++) {
        glActiveTexture(GL_TEXTURE0 + i + 1);
        glBindTexture(GL_TEXTURE_2D, s_renderData.textureIds.at(i));
    }

    shader.uploadIntArray("uTextures", 8, textureSlots);

    glBindVertexArray(s_renderData.quadVA);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);

    glDrawElements(GL_TRIANGLES, s_renderData.indexCount, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glDisableVertexAttribArray(4);

    glBindVertexArray(0);

    for (unsigned int i = 0; i < s_renderData.textureSlotsIndex; i++) {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    shader.detach();

    s_renderData.stats.drawCount++;
    s_renderData.indexCount = 0;
    s_renderData.textureSlotsIndex = 0;

    s_renderData.textureIds = std::array<uint32_t, 8>();
}

void Renderer::resetStats() {
    //memset(&s_renderData.stats, 0, sizeof(RenderStats));
    s_renderData.stats = {};
}

bi::Renderer::RenderStats& Renderer::getRenderStats () {
    return this->s_renderData.stats;
}

Renderer::~Renderer(){

    log("Destroyed Renderer!");
    delete[] s_renderData.quadBuffer;
}

void Renderer::clear(glm::vec4 color) {
    clear(color.r, color.g, color.b, color.a);
}

void Renderer::clear(float r, float g, float b, float a) {
    glm::vec4 color = color::fromRGB(r,g,b,a);
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Renderer::incrementDrawCounters() {
    s_renderData.indexCount += 6;
    s_renderData.stats.quadCount++;
}

void Renderer::reevaluateBatchSpace() {
    if (s_renderData.indexCount >= maxIndexCount || s_renderData.textureSlotsIndex >= 8) {
        endFlushBegin();
    }
}

Renderer& Renderer::drawText(std::array<char, 256> text, glm::vec2 position, Font& f, glm::vec4 color, float scale) {
    std::string str(text.data());
    drawText(str, position, f, color, scale);
    return *this;
}

Renderer& Renderer::drawText(std::string text, glm::vec2 position, Font& f, glm::vec4 color, float scale) {

    reevaluateBatchSpace();
    float textureIndex = getTextureIndex(f.textureId);

    f.updateBuffers(text, position, s_renderData.currentLocationPtr, color::fromRGB(color) , scale, textureIndex);
    // each character is a quad
    s_renderData.indexCount += 6 * text.length();
    s_renderData.stats.quadCount += text.length();
    return *this;
}

Renderer& Renderer::drawTile(Tile& tile, glm::vec4 color) {
    drawTexture(tile.getPosition(), tile.getTileSize(), color, tile.getTextureId(), 0, tile.getTexCoords());
    return *this;
}

float Renderer::getTextureIndex(unsigned int texId) {

    float textureIndex = 0.0f;
    for (unsigned int i = 0; i < maxTextures; i++) {
        if (s_renderData.textureIds[i] == texId) {
            textureIndex = (float) (i + 1);
            break;
        }
    }
    if (textureIndex == 0.0f) {
        textureIndex = (float) s_renderData.textureSlotsIndex + 1;
        s_renderData.textureIds[s_renderData.textureSlotsIndex] = texId;
        // not existing
        s_renderData.textureSlotsIndex++;
    }
    return textureIndex;
}

void Renderer::setDefaultBlend() {
    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::setAdditiveBlend() {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}



