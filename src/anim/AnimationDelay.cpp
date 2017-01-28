//
// Created by Bruno Fortunato on 06/06/16.
//

#include "tinto/anim/AnimationDelay.h"

namespace tinto {

    void AnimationDelay::step(GameTime *gameTime) {
        if (target == nullptr) {
            return;
        }

        if (isComplete()) {
            return;
        }

        this->time += gameTime->getElapsedTime();
    }


    bool AnimationDelay::isComplete() {
        return time >= value;
    }

}