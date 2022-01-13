#include "bismuth/iomanager.hpp"
#include <bismuth/primitives.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <array>
#include <bismuth/font.hpp>
#include <bismuth/logging.hpp>
#include <exception>
#include <glad/glad.h>
#include <iostream>
#include <ostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>


using namespace bi;
Font::Font() { }

Font::~Font() {}

void Font::updateBuffers(std::string text, glm::vec2 position, QuadVertex*& quadVertex, glm::vec4 color, float scale , float renderTexId) {

    glm::vec2 pos = position;
    for (auto& ch : text) {
        std::string s;
        s.push_back(ch);
        if (characters.count(ch) == 0) {
            //throw std::runtime_error("Char: " + s + " isn't found");
            log("Failed to find char: " + s);
            break;
        }
        //log("next char: " + s);
        Character& c = characters.at(ch);

        glm::vec2 texcoordBR = {(c.x + c.width) / (float)fontInfo.scaleW, (c.y + c.height) / (float)fontInfo.scaleH };
        glm::vec2 texcoordTR = {(c.x + c.width) / (float)fontInfo.scaleW, c.y / (float)fontInfo.scaleH };
        glm::vec2 texcoordTL = {c.x / (float)fontInfo.scaleW, c.y / (float)fontInfo.scaleH };
        glm::vec2 texcoordBL = {c.x / (float)fontInfo.scaleW, (c.y + c.height) / (float)fontInfo.scaleH };


        glm::vec3 posBR = {pos.x + (c.width + c.xoffset) * scale, pos.y + (c.height + c.yoofset) * scale, 0.0f};
        glm::vec3 posTR = {pos.x + (c.width + c.xoffset) * scale, pos.y + c.yoofset * scale, 0.0f};
        glm::vec3 posTL = {pos.x + c.xoffset * scale, pos.y + c.yoofset * scale, 0.0f};
        glm::vec3 posBL = {pos.x + c.xoffset * scale, pos.y + (c.height + c.yoofset) * scale, 0.0f};
        /*
           log("-------------------------------");
           log(glm::to_string(texcoordBR));
           log(glm::to_string(texcoordTR));
           log(glm::to_string(texcoordTL));
           log(glm::to_string(texcoordBL));
           log("-------------------------------");
           */
        quadVertex->texId = renderTexId;
        quadVertex->position = posBR;
        quadVertex->color = color;
        quadVertex->texcoords = texcoordBR;
        quadVertex->type = 1.0f;
        quadVertex++;

        quadVertex->texId = renderTexId;
        quadVertex->position = posTR;
        quadVertex->color = color;
        quadVertex->texcoords = texcoordTR;
        quadVertex->type = 1.0f;
        quadVertex++;

        quadVertex->texId = renderTexId;
        quadVertex->position = posTL;
        quadVertex->color = color;
        quadVertex->texcoords = texcoordTL;
        quadVertex->type = 1.0f;
        quadVertex++;

        quadVertex->texId = renderTexId;
        quadVertex->position = posBL;
        quadVertex->color = color;
        quadVertex->texcoords = texcoordBL;
        quadVertex->type = 1.0f;
        quadVertex++;

        pos.x += c.xadvance * scale;
    }

}
std::vector<std::string> Font::split(std::string str,std::string sep){
    char* cstr=const_cast<char*>(str.c_str());
    char* current;
    std::vector<std::string> arr;
    current=strtok(cstr,sep.c_str());
    while(current!=NULL){
        arr.push_back(current);
        current=strtok(NULL,sep.c_str());
    }
    return arr;
}

void Font::loadFnt(std::string filePath) {

    std::ifstream file(filePath);
    std::string line;
    std::vector<std::string> lines;

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    std::string delimiter = "=";

    std::string faceLine = lines.at(0);
    std::string token;

    std::vector<std::string> info1 = split(lines.at(0), "=");
    fontInfo.face = getInQuotes(info1.at(1));
    fontInfo.size = getDigit(info1.at(2));
    fontInfo.bold = getDigit(info1.at(3));
    fontInfo.italic = getDigit(info1.at(4));

    // last line isnt needed
    std::vector<std::string> info2 = split(lines.at(1), "=");
    fontInfo.lineHeight = getDigit(info2.at(1));
    fontInfo.base = getDigit(info2.at(2));
    fontInfo.scaleW = getDigit(info2.at(3));
    fontInfo.scaleH = getDigit(info2.at(4));
    fontInfo.pages = getDigit(info2.at(5));
    fontInfo.packed = getDigit(info2.at(6));

    std::vector<std::string> info3 = split(lines.at(2), "=");
    fontInfo.file = getInQuotes(info3[2]);
    std::vector<std::string> info4 = split(lines.at(3), "=");
    int charLines = getDigit(info4[1]);


    for (int i = 4; i <= charLines; i++) {
        std::vector<std::string> l = split(lines.at(i), "=");
        Character ch;
        ch.charId = getDigit(l[1]);
        ch.x = getDigit(l[2]);
        ch.y = getDigit(l[3]);
        ch.width = getDigit(l[4]);
        ch.height = getDigit(l[5]);
        ch.xoffset = getDigit(l[6]);
        ch.yoofset = getDigit(l[7]);
        ch.xadvance = getDigit(l[8]);
        ch.page = getDigit(l[9]);
        ch.chnl = getDigit(l[10]);
        this->characters.insert({ch.charId, ch});
    }

    textureId = bi::ioManager().assetmanager->loadTexture("resources/assets/fonts/" + fontInfo.file);
}

int Font::getDigit(std::string text){
    std::regex rgx("(^-?[0-9]+)");
    std::smatch match;

    if (std::regex_search(text, match, rgx))
    {

        //std::cout << match[1] << std::endl;

        return std::stoi(match[1]);
    }

    return 1;
}
std::string Font::getInQuotes(std::string text) {

    std::regex rgx("\"(.*?)\"");
    std::smatch match;

    if (std::regex_search(text, match, rgx))
    {
        return match[1];
    }
    return text;
}

glm::vec2 Font::getSizeOfText(std::string text, float scale) {
    float width = 0, height = 0;
    for (auto& ch : text) {
        if (characters.count(ch) == 0) {
            return { width, height };
        }
        Character& c = characters.at(ch);
        width += c.xadvance * scale;
        height = std::max((c.height + c.yoofset) * scale, height);
    }
    return { width, height };

}

std::vector<Character> Font::getCharacters(std::string text) {
    std::vector<Character> chars;
    for (char& ch : text) {
        if (characters.count(ch) > 0)
            chars.push_back(characters.at(ch));
    }
    log("found: " + std::to_string(chars.size()));
    return chars;
}


