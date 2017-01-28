//
// Created by Bruno Fortunato on 23/05/16.
//

#include "tinto/anim/ParallelAnimation.h"

namespace tinto {

    ParallelAnimation::~ParallelAnimation() {
        for (auto c : children) {
            delete c;
        }
    }

    void ParallelAnimation::addChild(Animation *child) {
        children.push_back(child);
    }

    ParallelAnimation *ParallelAnimation::create(std::initializer_list<Animation *> animations, bool loop) {
        auto parallel = new ParallelAnimation();
        parallel->loop = loop;

        for (auto anim : animations) {
            parallel->addChild(anim);
        }

        return parallel;
    }


    void ParallelAnimation::step(GameTime *gameTime) {
        for (auto anim : children) {
            anim->step(gameTime);
        }
    }

    bool ParallelAnimation::isComplete() {
        for (auto anim : children) {
            if (!anim->isComplete()) {
                return false;
            }
        }

        return true;
    }


    void ParallelAnimation::reset() {
        for (auto anim : children) {
            anim->reset();
        }
    }

}