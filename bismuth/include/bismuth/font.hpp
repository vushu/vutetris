#pragma once
#include <array>
#include <bismuth/primitives.hpp>
#include <glm/glm.hpp>
#include <map>
#include <vector>
#include <string>

namespace bi {
    struct FontInfo {
        std::string face;
        unsigned int size;
        bool bold, italic;
        unsigned int lineHeight, base, scaleW, scaleH, pages, packed;
        std::string file;

    };
    struct Character {
        int charId;
        int x,y, width, height, xoffset, yoofset, xadvance, page, chnl;
    };


    class Font {

        public:
            Font();
            void loadFnt(std::string filePath);
            ~Font();
            void updateBuffers(std::string text, glm::vec2 position, QuadVertex*& quadVertex, glm::vec4 color, float scale, float renderTexId);
            unsigned int textureId;
            std::vector<Character> getCharacters(std::string text);
            glm::vec2 getSizeOfText(std::string text, float scale);

        private:
            FontInfo fontInfo;
            std::string face;
            std::string mfontFilePath;
            float mfontSize;
            std::map<char, Character> characters;
            std::vector<std::string> split(std::string str, std::string sep);
            int getDigit(std::string text);
            std::string getInQuotes(std::string text);

    };
}
