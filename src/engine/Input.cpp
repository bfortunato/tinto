//
// Created by Bruno Fortunato on 03/06/16.
//

#include "tinto/engine/Input.h"
#include "tinto/engine/GameEngine.h"
#include "tinto/engine/Metrics.h"

namespace tinto {

    void Input::init() {

    }

    Touch *Input::getTouch(uint index) {
        if (_touches->size() > index) {
            return _touches->at(index);
        }

        return nullptr;
    }

    void Input::handle(SDL_Event *event) {
        if (event->type == SDL_MOUSEBUTTONDOWN) {
            Touch *touch = new Touch();
            touch->position = this->normalizedMousePosition(event);
            touch->state = TouchState::TOUCH_STATE_BEGAN;

            touchCount++;
            _touches->push_back(touch);

            mousePosition = _engine->metrics->toLogical(GPoint(event->motion.x, event->motion.y));
        }

        if (event->type == SDL_MOUSEBUTTONUP) {
            Touch *touch = new Touch();
            touch->position = this->normalizedMousePosition(event);
            touch->state = TouchState::TOUCH_STATE_ENDED;

            touchCount++;
            _touches->push_back(touch);

            mousePosition = _engine->metrics->toLogical(GPoint(event->motion.x, event->motion.y));
        }
        if (event->type == SDL_MOUSEMOTION) {
            Touch *touch = new Touch();
            touch->position = this->normalizedMousePosition(event);
            touch->state = TouchState::TOUCH_STATE_MOVED;

            touchCount++;
            _touches->push_back(touch);

            mousePosition = _engine->metrics->toLogical(GPoint(event->motion.x, event->motion.y));
        }
        if (event->type == SDL_FINGERDOWN) {
            Touch *touch = new Touch();
            touch->position = GPoint(event->tfinger.x * _engine->metrics->logicalSize.width,
                                     event->tfinger.y * _engine->metrics->logicalSize.height);
            touch->state = TouchState::TOUCH_STATE_BEGAN;

            touchCount++;
            _touches->push_back(touch);

            mousePosition = GPoint(event->tfinger.x * _engine->metrics->logicalSize.width,
                                   event->tfinger.y * _engine->metrics->logicalSize.height);
        }
        if (event->type == SDL_FINGERUP) {
            Touch *touch = new Touch();
            touch->position = GPoint(event->tfinger.x * _engine->metrics->logicalSize.width,
                                     event->tfinger.y * _engine->metrics->logicalSize.height);
            touch->state = TouchState::TOUCH_STATE_ENDED;

            touchCount++;
            _touches->push_back(touch);

            mousePosition = GPoint(event->tfinger.x * _engine->metrics->logicalSize.width,
                                   event->tfinger.y * _engine->metrics->logicalSize.height);
        }
        if (event->type == SDL_FINGERMOTION) {
            Touch *touch = new Touch();
            touch->position = GPoint(event->tfinger.x * _engine->metrics->logicalSize.width,
                                     event->tfinger.y * _engine->metrics->logicalSize.height);
            touch->state = TouchState::TOUCH_STATE_MOVED;

            touchCount++;
            _touches->push_back(touch);

            mousePosition = GPoint(event->tfinger.x * _engine->metrics->logicalSize.width,
                                   event->tfinger.y * _engine->metrics->logicalSize.height);
        }
    }

    void Input::cleanup() {
        touchCount = 0;

        for (auto touch : *_touches) {
            delete touch;
        }

        _touches->clear();
    }

    GPoint Input::normalizedMousePosition(SDL_Event *event) {
        float x = event->motion.x / _engine->metrics->windowSize.width * _engine->metrics->logicalSize.width;
        float y = event->motion.y / _engine->metrics->windowSize.height * _engine->metrics->logicalSize.height;

        return GPoint(x, y);
    }

}



