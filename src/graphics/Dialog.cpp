//
// Created by Bruno Fortunato on 20/06/16.
//

#include "tinto/graphics/Dialog.h"

namespace tinto {

    void Dialog::init() {
        Node::init();

        if (background == nullptr) {
            SDL_Log("Background node not setted");
            throw std::exception();
        }

        active = false;

        addChild(background);

        rect.x = engine->metrics->rect.getCenter().x;
        rect.y = engine->metrics->rect.getCenter().y;
        rect.width = background->rect.width;
        rect.height = background->rect.height;

        background->rect.x = background->rect.width / 2;
        background->rect.y = background->rect.height / 2;
    }


    void Dialog::show() {
        active = true;

        float startY = engine->metrics->rect.y - rect.height / 2;
        float stopY = engine->metrics->rect.getCenter().y;

        animate(AnimationProperty::ALPHA, 0, 1, 500, AnimationEase::EASE_OUT);
        animate(AnimationProperty::Y, startY, stopY, 500, AnimationEase::EASE_OUT);
    }

    void Dialog::hide() {
        float startY = engine->metrics->rect.y - rect.height / 2;
        float stopY = engine->metrics->rect.getCenter().y;

        animate(AnimationProperty::ALPHA, 1, 0, 500, AnimationEase::EASE_IN);
        animate(AnimationProperty::Y, stopY, startY, 500, AnimationEase::EASE_IN);

        dispatchDelayed("dialog:hide:active", [this]() {
            active = false;
        }, 500);
    }

}


