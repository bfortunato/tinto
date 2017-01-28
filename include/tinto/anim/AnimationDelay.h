//
// Created by Bruno Fortunato on 06/06/16.
//

#ifndef TINTO_ANIMATIONDELAY_H
#define TINTO_ANIMATIONDELAY_H

#include "Animation.h"

namespace tinto {

    class AnimationDelay : public Animation {
    public:
        virtual bool isComplete() override;

        virtual void step(GameTime *gameTime) override;

        AnimationDelay(Node *target, float delay) : Animation(target) { value = delay; }
    };

}

#endif //TINTO_ANIMATIONDELAY_H
