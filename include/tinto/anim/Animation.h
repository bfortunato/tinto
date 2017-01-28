//
// Created by Bruno Fortunato on 23/05/16.
//

#ifndef TINTO_ANIMATION_H
#define TINTO_ANIMATION_H

#include <SDL.h>
#include "tinto/engine/GameTime.h"
#include "tinto/utils/Observable.h"

namespace tinto {

    class Node;

    enum class AnimationProperty {
        ALPHA,
        X,
        Y,
        WIDTH,
        HEIGHT,
        ROTATION,
        SCALEX,
        SCALEY
    };

    enum class AnimationEase {
        EASE_NONE,
        EASE_IN,
        EASE_OUT,
        EASE_IN_OUT
    };

    class Animation : public Observable {
    public:
        Animation(Node *target);

        virtual ~Animation();

        Node *target = nullptr;
        AnimationProperty property;
        AnimationEase ease = AnimationEase::EASE_NONE;
        float from = 0;
        float to = 0;
        Uint32 duration = 0; //milliseconds
        bool loop = false;
        bool canceled = false;

        virtual void step(GameTime *gameTime);

        virtual void reset();

        virtual bool isComplete();

        static Animation *create(
                Node *target,
                AnimationProperty property,
                float from,
                float to,
                Uint32 duration,
                AnimationEase ease = AnimationEase::EASE_NONE,
                bool loop = false);

        static Animation *delay(Node *target, float value);

        void cancel();

    protected:
        Uint32 time = 0;
        float value;

    private:
        void setProperty(float value);
    };

}

#endif //TINTO_ANIMATION_H
