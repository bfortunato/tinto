//

#include "tinto/anim/SerialAnimation.h"

namespace tinto {

//
// Created by Bruno Fortunato on 23/05/16.

    SerialAnimation::~SerialAnimation() {
        for (auto c : children) {
            delete c;
        }
    }

    void SerialAnimation::addChild(Animation *child) {
        children.push_back(child);
        this->currentAnimationIndex = 0;
    }


    SerialAnimation *SerialAnimation::create(std::initializer_list<Animation *> animations, bool loop) {
        auto serial = new SerialAnimation();
        serial->loop = loop;

        for (auto anim : animations) {
            serial->addChild(anim);
        }

        return serial;
    }

    void SerialAnimation::step(GameTime *gameTime) {
        auto current = children.at(currentAnimationIndex);
        current->step(gameTime);

        if (current->isComplete()) {
            currentAnimationIndex++;
        }

        if (loop) {
            if (isComplete()) {
                reset();
            }
        }
    }


    bool SerialAnimation::isComplete() {
        return currentAnimationIndex >= children.size();
    }

    void SerialAnimation::reset() {
        currentAnimationIndex = 0;
        for (auto anim : children) {
            anim->reset();
        }
    }

}



