#include <bismuth/logging.hpp>
#include <bismuth/audiomanager.hpp>
#include <algorithm>
#include <stdexcept>
#include <map>
#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio/miniaudio.h>
using namespace bi;


AudioManager::~AudioManager() {
    ma_device_uninit(&device);
    log("AudioManager Destroyed");
}

//Safe volumeLimit
float AudioManager::volumeLimit = 1.5f;
std::map<std::string, std::shared_ptr<Sound>> AudioManager::sounds;

void AudioManager::init() {
    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format   = SAMPLE_FORMAT;
    deviceConfig.playback.channels = CHANNEL_COUNT;
    deviceConfig.sampleRate        = SAMPLE_RATE;
    deviceConfig.dataCallback      = dataCallback;
    //deviceConfig.dataCallback      = simpleCallback;
    deviceConfig.pUserData         = NULL;

    //ma_event_init(&stopEvent);
    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
        throw std::runtime_error("Failed to init audiodevice");
    }

    log("AudioManager initialized");
}

void AudioManager::start() {
    if (deviceStopped)
    {
        if (ma_device_start(&device) != MA_SUCCESS) {
            bi::log("Failed to start playback device");
            throw std::runtime_error("Failed to start audiodevice");
        }
        bi::log("Sound Device started: OK");
        deviceStopped = false;
    }
}


void AudioManager::stop() {
    //ma_event_signal(&stopEvent);
    if (!deviceStopped) {
        if (ma_device_stop(&device) == MA_SUCCESS) {
            log("OK stopped device");
            deviceStopped = true;
        }
    }
}

void AudioManager::setMaxVolume(float volume) {
    volumeLimit = volume;
}

std::string AudioManager::addSound(std::string soundFile) {
    std::string file = soundFile;
    std::shared_ptr<Sound> sound = std::make_shared<Sound>(soundFile);
    sound->init();
    bi::log("Adding sound", soundFile);
    this->sounds.emplace(sound->filepath, std::move(sound));
    return file;
}

Sound& AudioManager::getSound(std::string soundFile) {
    if (this->sounds.count(soundFile) > 0)
        return *this->sounds.at(soundFile);
    return *this->sounds.at(addSound(soundFile));
}

void AudioManager::playSound(std::string soundFile, bool rewind) {
    getSound(soundFile).playSound(rewind);
}

ma_uint32 AudioManager::readMixPcmFrames(ma_decoder* pDecoder, float* pOutputF32, ma_uint32 frameCount, float volume = 1) {
    ma_result result;
    float temp[4096];
    ma_uint32 tempCapInFrames = ma_countof(temp) / CHANNEL_COUNT;
    ma_uint32 totalFramesRead = 0;

    while (totalFramesRead < frameCount) {
        ma_uint64 iSample;
        ma_uint64 framesReadThisIteration;
        ma_uint32 totalFramesRemaining = frameCount - totalFramesRead;
        ma_uint32 framesToReadThisIteration = tempCapInFrames;

        if (framesToReadThisIteration > totalFramesRemaining) {
            framesToReadThisIteration = totalFramesRemaining;
        }

        result = ma_decoder_read_pcm_frames(pDecoder, temp, framesToReadThisIteration, &framesReadThisIteration);

        if (result != MA_SUCCESS || framesReadThisIteration == 0) {
            break;
        }

        for (iSample = 0; iSample < framesReadThisIteration*CHANNEL_COUNT; ++iSample) {
            pOutputF32[totalFramesRead*CHANNEL_COUNT + iSample] += temp[iSample] * volume;
        }

        totalFramesRead += (ma_uint32) framesReadThisIteration;

        if (framesReadThisIteration < (ma_uint32) framesToReadThisIteration) {
            break;  /* Reached EOF. */
        }
    }
    return totalFramesRead;
}

void AudioManager::dataCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {

    float* pOutputF32 = (float*)pOutput;

    MA_ASSERT (pDevice->playback.format == SAMPLE_FORMAT);

    for (auto const& [key, sound] : sounds) {

        if (sound->rewind) {
            ma_decoder_seek_to_pcm_frame(&sound->decoder, 0);
            sound->rewind = false;
        }
        else if (!sound->isPause && !sound->isDone) {
            //ma_decoder_seek_to_pcm_frame(&sound->decoder, 0);
            // clamping volume
            sound->volume = std::max(std::min(sound->volume, volumeLimit), 0.0f);

            ma_uint32 frameRead = readMixPcmFrames(&sound->decoder, pOutputF32, frameCount, sound->volume);
            if (frameRead < frameCount) {
                if (sound->loop) {
                    // loop sound
                    ma_decoder_seek_to_pcm_frame(&sound->decoder, 0);
                }
                else
                    sound->isDone = true;
            }
        }
    }

    (void)pInput;
}
