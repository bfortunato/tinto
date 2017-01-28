//
// Created by Bruno Fortunato on 03/06/16.
//

#ifndef TINTO_INPUT_H
#define TINTO_INPUT_H

#include <vector>
#include "tinto/utils/Geometry.h"

namespace tinto {

    class GameEngine;

    enum TouchState {
        TOUCH_STATE_BEGAN,
        TOUCH_STATE_MOVED,
        TOUCH_STATE_STATIONARY,
        TOUCH_STATE_ENDED,
        TOUCH_STATE_CANCELED
    };

    class Touch {
    public:
        GPoint position;
        TouchState state = TOUCH_STATE_CANCELED;

    private:
        friend class GameEngine;

        friend class Input;
    };

    class Input {
    public:
        Input(GameEngine *engine) : _engine(engine) {
            _touches = new std::vector<Touch *>();
        };

        ~Input() {
            delete _touches;
        }

        void init();

        void handle(SDL_Event *event);

        void cleanup();

        Touch *getTouch(uint index);

        uint touchCount = 0;
        GPoint mousePosition;

    private:
        GameEngine *_engine;
        std::vector<Touch *> *_touches;
        GSize _windowSize;

        GPoint normalizedMousePosition(SDL_Event *event);

        friend class GameEngine;
    };

}

#endif //TINTO_INPUT_H
