//
// Created by Bruno Fortunato on 06/06/16.
//

#include "tinto/graphics/NodeWrapper.h"

namespace tinto {

    void NodeWrapper::init() {
        Node::init();
    }

    void NodeWrapper::update(GameTime *gameTime) {
        _wrapped->update(gameTime);
    }

    void NodeWrapper::draw(GameTime *gameTime) {
        _wrapped->rect = rect;
        _wrapped->alpha = alpha;
        _wrapped->rotation = rotation;
        _wrapped->active = active;
        _wrapped->scaleX = scaleX;
        _wrapped->scaleY = scaleY;
        _wrapped->origin = origin;
        _wrapped->parent = parent;
        _wrapped->active = active;

        _wrapped->draw(gameTime);
    }

}