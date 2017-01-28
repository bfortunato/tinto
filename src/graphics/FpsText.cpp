//
// Created by Bruno Fortunato on 01/06/16.
//

#include "tinto/graphics/FpsText.h"

#include <sstream>

namespace tinto {

    void FpsText::update(GameTime *gameTime) {
        this->_elapsedTime += gameTime->getElapsedTime();

        if (_elapsedTime > 1000) {
            std::stringstream fps;
            fps << "fps: " << gameTime->calculateFrameRate();
            text = fps.str();
            invalidate();
            _elapsedTime = 0;
        }

        Node::update(gameTime);
    }

}