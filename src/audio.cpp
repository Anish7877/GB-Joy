#include "../include/audio.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <stdexcept>

Audio::Audio(){
        if(SDL_Init(SDL_INIT_AUDIO) < 0){
                throw std::runtime_error(SDL_GetError());
        }
        SDL_zero(want);
        want.freq = 44100;
        want.format = AUDIO_F32;
        want.channels = 1;
        want.samples = 1024;
        want.callback = NULL;
        audio_device = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
        if (audio_device != 0) {
                SDL_PauseAudioDevice(audio_device, 0);
        }
}

Audio::~Audio(){
        if (audio_device != 0) SDL_CloseAudioDevice(audio_device);
        SDL_Quit();
}

bool Audio::audio_device_check() const noexcept{
        return audio_device != 0;
}

void Audio::update_audio_device_data(float sample) noexcept{
        if (SDL_GetQueuedAudioSize(audio_device) < 4096 * sizeof(float)) {
                SDL_QueueAudio(audio_device, &sample, sizeof(float));
        }
}
