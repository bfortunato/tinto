//
// Created by Bruno Fortunato on 03/06/16.
//

#include "tinto/graphics/Button.h"

namespace tinto {

    void Button::update(GameTime *gameTime) {
        if (engine->input->touchCount > 0) {
            Touch *touch = engine->input->getTouch(engine->input->touchCount - 1);
            if (hitTest(touch->position)) {
                if (touch->state == TouchState::TOUCH_STATE_BEGAN) {
                    this->state = ButtonState::BUTTON_STATE_PUSHED;

                    dispatch("button:down", [this]() { invoke("down"); });
                }
            }

            if (state == BUTTON_STATE_PUSHED) {
                if (touch->state == TOUCH_STATE_ENDED) {
                    if (hitTest(touch->position)) {
                        dispatch("button:touch", [this]() { invoke("touch"); });
                    }

                    state = BUTTON_STATE_NORMAL;

                    invoke("up");
                }
            }
        }

        _pushedStateNode->active = this->state == BUTTON_STATE_PUSHED;
        _normalStateNode->active = this->state == BUTTON_STATE_NORMAL;

        Node::update(gameTime);
    }


    void Button::draw(GameTime *gameTime) {
        Node::draw(gameTime);
    }


    void Button::setBackgroundNode(Node *background) {
        _backgroundNode = background;
        addChild(_backgroundNode);
    }

    void Button::setNormalStateNode(Node *normalState) {
        _normalStateNode = normalState;
        addChild(_normalStateNode);
    }

    void Button::setPushedStateNode(Node *pushedState) {
        _pushedStateNode = pushedState;
        _pushedStateNode->active = false;

        addChild(_pushedStateNode);
    }

}