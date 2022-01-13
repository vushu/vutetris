#pragma once
#include <memory>
#include <miniaudio/miniaudio.h>
#include "sound.hpp"
#include <map>
#define SAMPLE_FORMAT   ma_format_f32
#define CHANNEL_COUNT   2
#define SAMPLE_RATE     48000
namespace bi  {
    class AudioManager {

        public:
            // constructors, asssignment, destructor
            AudioManager () {};
            ~AudioManager ();
            void init();
            std::string addSound(std::string soundFile);
            Sound& getSound(std::string file);
            void playSound(std::string file, bool rewind = true);

            void start();
            void stop();
            void setMaxVolume(float volume);

        private:
            bool deviceStopped = true;
            static float volumeLimit;
            ma_event stopEvent;
            ma_device_config deviceConfig;
            ma_device device;
            static void dataCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);
            static ma_uint32 readMixPcmFrames(ma_decoder* pDecoder, float* pOutputF32, ma_uint32 frameCount, float volume);
            static std::map<std::string, std::shared_ptr<Sound>> sounds;
    };
}
