//
// Created by Bruno Fortunato on 30/05/16.
//

#include <SDL.h>

#include "tinto/audio/Music.h"

namespace tinto {

    void Music::load(std::string path) {
        _music = Mix_LoadMUS(path.c_str());

        if (_music == nullptr) {
            SDL_Log("Cannot load music %s", path.c_str());
            throw std::exception();
        }
    }

    void Music::play() {
        if (_music != nullptr) {
            Mix_PlayMusic(_music, loop ? -1 : 0);
        }
    }

    void Music::pause() {
        if (_music != nullptr) {
            if (Mix_PlayingMusic()) {
                Mix_PausedMusic();
            }
        }
    }

    void Music::stop() {
        if (_music != nullptr) {
            Mix_HaltMusic();
        }
    }

    void Music::destroy() {
        if (_music != nullptr) {
            Mix_FreeMusic(_music);
            _music = nullptr;
        }
    }

}