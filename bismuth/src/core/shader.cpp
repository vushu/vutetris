#include <bismuth/logging.hpp>
#include <bismuth/shader.hpp>
#include <fstream>
#include <glm/glm.hpp>
#include <regex>
#include <stdexcept>
#include <vector>
#include <string>
#include <bismuth/glhelper.hpp>
using namespace bi;

Shader::Shader(std::string filepath) {
    this->filepath = filepath;
    std::ifstream ifs(filepath);
    if (ifs) {
        std::string content((std::istreambuf_iterator<char>(ifs)),
                (std::istreambuf_iterator<char>()));
        parseShader(content);
    }
}

void Shader::parseShader(std::string source) {
    std::string regex = "(#type)( )+([a-zA-Z]+)";
    std::vector<std::string> splitted = split(source, regex);

    if (splitted.size() < 2) {
        throw std::runtime_error("Shader isn't recognized");
    }

    size_t index = source.find("#type") + 6;
    size_t eol = source.find("\n", index);
    std::string firstPattern = trim(source.substr(index, eol-index));

    index = source.find("#type", eol) + 6;
    eol = source.find("\n", index);
    std::string secondPattern = trim(source.substr(index, eol - index));

    setSource(firstPattern, splitted[1].erase(0,1));
    setSource(secondPattern, splitted[2].erase(0,1));
}

std::vector<std::string> Shader::split(const std::string& str, const std::string& regex) {
    std::regex re(regex);
    std::sregex_token_iterator
        first{str.begin(), str.end(), re, -1},
        last;
    return {first, last};
}

std::string Shader::trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

void Shader::setSource(const std::string& pattern, const std::string& source) {
    if (pattern.compare("vertex") == 0) {
        this->vertexSource = source;
    }
    else if (pattern.compare("fragment") == 0) {
        this->fragmentSource = source;
    }
    else {
        throw std::runtime_error("Couldn't determine shader sources");
    }
}

bool Shader::compile() {
    vertexId = glhelper::compileVertexShader(vertexSource);
    fragmentId = glhelper::compileFragmentShader(fragmentSource);
    shaderProgramId = glhelper::linkShaders(vertexId, fragmentId);
    log("Done linking");
    free();
    bi::log("ProgramId: " +  std::to_string(shaderProgramId));
    bool success = vertexId > 0 && fragmentId > 0 && shaderProgramId > 0;
    bi::log("shaders compiled: " + std::to_string(success));
    this->compiled = success;
    if (!success) {
        throw std::runtime_error("Failed to compile shader");
    }
    return success;
}

void Shader::use() {
    if (!isUsed) {
        glUseProgram(shaderProgramId);
        isUsed = true;
    }
}

void Shader::detach() {
    glUseProgram(0);
    isUsed = false;
}

void Shader::uploadUniformMat3(std::string varName, glm::mat3& mat3) {
    glhelper::uploadUniformMat3(shaderProgramId, varName, mat3);
}

void Shader::uploadUniformVec2(std::string varName, glm::vec2& vec2) {
    glhelper::uploadUniformVec2(shaderProgramId, varName, vec2);
}

void Shader::uploadUniformVec3(std::string varName, glm::vec3& vec3) {
    glhelper::uploadUniformVec3(shaderProgramId, varName, vec3);
}

void Shader::uploadUniformMat4(std::string varName, glm::mat4 mat4) {
    glhelper::uploadUniformMat4(shaderProgramId, varName, mat4);
}

void Shader::uploadUniformFloat(std::string varName, float value) {
    glhelper::uploadUniformFloat(shaderProgramId, varName.c_str(), value);
}

void Shader::uploadUniformInt(std::string varName, int value) {
    glhelper::uploadUniformInt(shaderProgramId, varName.c_str(), value);
}

void Shader::uploadIntArray(std::string varName,int size, int* location) {
    glhelper::uploadUniformIntArray(shaderProgramId, varName, size, location);
}

void Shader::uploadIntArray(std::string varName,int size, const int* location) {
    glhelper::uploadUniformIntArray(shaderProgramId, varName, size, location);
}

void Shader::uploadIntArray2(std::string varName,int size, int location[]) {
    glhelper::uploadUniformIntArray2(shaderProgramId, varName, size, location);
}
void Shader::free() {
    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
    bi::log("Destroying VERTEX AND FRAGMENT DONE");

}

Shader::~Shader() {
    bi::log("Shader destroyed");
}
