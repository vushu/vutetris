#include <bismuth/logging.hpp>
#include <bismuth/sound.hpp>
#include "miniaudio/miniaudio.h"
#include <stdexcept>
using namespace bi;

ma_uint64 playHead;

Sound::Sound(std::string filepath) {
    this->filepath = filepath;
    this->decoderConfig = ma_decoder_config_init(SAMPLE_FORMAT, CHANNEL_COUNT, SAMPLE_RATE);
}

Sound::~Sound() {
    ma_decoder_uninit(&decoder);
    log("Sound destroyed", filepath);
}

void Sound::playSound(bool rewind) {
    if (rewind) {
        rewindSound();
    }
    this->isPause = false;
}

void Sound::pauseSound() {
    this->isPause = true;
}

void Sound::stopSound() {
    this->isPause = true;
    this->rewindSound();
}

void Sound::rewindSound() {
    this->isDone = false;
    this->rewind = true;
}

void Sound::incrementVolume(float volume) {
    this->volume += volume;
}

void Sound::decrementVolume(float volume) {
    this->volume -= volume;
}


void Sound::setLoop(bool enable) {
    this->loop = enable;
}

void Sound::setVolume(float volume) {
    this->volume = volume;
}

void Sound::init() {
    ma_result result = ma_decoder_init_file(filepath.c_str(), &decoderConfig, &decoder);

    if (result != MA_SUCCESS) {
        throw std::runtime_error("Failed to load file");
    }
    bi::log("Sound initialized: ", filepath);

}
