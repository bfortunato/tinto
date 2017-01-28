//
// Created by Bruno Fortunato on 20/05/16.
//

#include <SDL.h>
#include <algorithm>

#include "tinto/engine/GameTime.h"

#define FPS 60

namespace tinto {

    void GameTime::delay() {
        int delay = (1000 / FPS) - computationTime;
        if (delay > 0) {
            SDL_Delay(delay);
        }
    }

    void GameTime::beginFrame() {
        this->frameBeginTime = SDL_GetTicks();
    }

    void GameTime::endFrame() {
        this->computationTime = SDL_GetTicks() - this->frameBeginTime;
    }

    float GameTime::calculateFrameRate() {
        if (computationTime != 0) {
            return 1000 / this->elapsedTime;
        }

        return 60;
    }

    void GameTime::step() {
        this->elapsedTime = getTotalTime() - this->lastUpdateTime;
        this->lastUpdateTime = SDL_GetTicks();
    }

    Uint32 GameTime::getElapsedTime() {
        return elapsedTime;
    }

    float GameTime::getElapsedTimeF() {
        return static_cast<float>(elapsedTime) / 1000.0f;
    }

    Uint32 GameTime::getTotalTime() {
        return SDL_GetTicks();
    }

}
