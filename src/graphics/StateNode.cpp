//
// Created by Bruno Fortunato on 07/06/16.
//

#include "tinto/graphics/StateNode.h"

namespace tinto {

    void StateNode::addState(std::string state, Node *node) {
        states.push_back(_State(state, node));

        node->active = false;

        addChild(node);
    }

    void StateNode::setState(std::string state) {
        for (auto s : states) {
            s.node->active = s.state == state;
        }
    }

}


