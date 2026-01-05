#ifndef AUDIO_HPP
#define AUDIO_HPP
#include <SDL2/SDL_audio.h>

class Audio{
        public:
                explicit Audio();
                ~Audio();
                static constexpr float cycles_per_sample{4194304.0f / 44100.0f};
                float get_audio_accumulator() const noexcept{return audio_accumulator;}
                void set_audio_accumulator(float new_val) {audio_accumulator = new_val;}
                bool audio_device_check() const noexcept;
                void update_audio_device_data(float sample) noexcept;
        private:
                SDL_AudioDeviceID audio_device{};
                SDL_AudioSpec want{};
                SDL_AudioSpec have{};
                float audio_accumulator{0.0f};
};
#endif
