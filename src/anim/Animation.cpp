//
// Created by Bruno Fortunato on 23/05/16.
//

#include "tinto/anim/Animation.h"
#include "tinto/easing/Easing.h"
#include "tinto/graphics/Node.h"
#include "tinto/anim/AnimationDelay.h"

namespace tinto {

    using namespace tinto::easing;

    Animation::Animation(Node *target) : target(target) {

    }

    void Animation::step(GameTime *gameTime) {
        if (canceled) {
            return;
        }

        if (target == nullptr) {
            return;
        }

        if (time == 0) {
            value = from;
        }

        if (isComplete()) {
            return;
        }

        this->time += gameTime->getElapsedTime();

        float t = 0;
        switch (ease) {
            case AnimationEase::EASE_NONE:
                t = Linear::easeNone(time, 0, 1, duration);
                break;
            case AnimationEase::EASE_IN:
                t = Cubic::easeIn(time, 0, 1, duration);
                break;
            case AnimationEase::EASE_OUT:
                t = Cubic::easeOut(time, 0, 1, duration);
                break;
            case AnimationEase::EASE_IN_OUT:
                t = Cubic::easeInOut(time, 0, 1, duration);
                break;
        }

        float delta = to - from;
        value = delta * t;
        value += from;

        setProperty(value);

        if (isComplete()) {
            setProperty(to);
            this->invoke("complete", nullptr);

            if (loop) {
                reset();
            }
        }
    }

    void Animation::setProperty(float value) {
        switch (property) {
            case AnimationProperty::X:
                target->rect.x = value;
                break;
            case AnimationProperty::Y:
                target->rect.y = value;
                break;
            case AnimationProperty::WIDTH:
                target->rect.width = value;
                break;
            case AnimationProperty::HEIGHT:
                target->rect.height = value;
                break;
            case AnimationProperty::ALPHA:
                target->alpha = value;
                break;
            case AnimationProperty::ROTATION:
                target->rotation = value;
                break;
            case AnimationProperty::SCALEX:
                target->scaleX = value;
                break;
            case AnimationProperty::SCALEY:
                target->scaleY = value;
                break;
        }
    }

    bool Animation::isComplete() {
        return canceled || (to > from ? value >= to : value <= to);
    }

    void Animation::reset() {
        value = from;
        time = 0;
    }

    Animation *Animation::create(Node *target, AnimationProperty property, float from, float to, Uint32 duration,
                                 AnimationEase ease, bool loop) {
        auto anim = new Animation(target);
        anim->property = property;
        anim->from = from;
        anim->to = to;
        anim->duration = duration;
        anim->ease = ease;
        anim->loop = loop;

        return anim;
    }


    Animation *Animation::delay(Node *target, float value) {
        auto anim = new AnimationDelay(target, value);
        return anim;
    }


    void Animation::cancel() {
        canceled = true;
    }

    Animation::~Animation() {
    }

}












