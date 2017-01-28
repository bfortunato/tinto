//
// Created by Bruno Fortunato on 30/05/16.
//

#include <SDL.h>

#include "tinto/audio/Sound.h"

namespace tinto {

    void Sound::load(std::string path) {
        _chunk = Mix_LoadWAV(path.c_str());

        if (_chunk == nullptr) {
            SDL_Log("Cannot load sound %s: %s", path.c_str(), SDL_GetError());
            throw std::exception();
        }
    }

    void Sound::play() {
        if (_chunk != nullptr) {
            Mix_PlayChannel(_channel, _chunk, loop ? -1 : 0);
        }
    }


    void Sound::pause() {
        if (_chunk != nullptr) {
            Mix_Pause(_channel);
        }
    }

    void Sound::stop() {
        if (_chunk != nullptr) {
            Mix_HaltChannel(-1);
        }
    }

    void Sound::destroy() {
        if (_chunk != nullptr) {
            Mix_FreeChunk(_chunk);
            _chunk = nullptr;
        }
    }

}
