//
// Created by Bruno Fortunato on 07/06/16.
//

#ifndef TINTO_STATENODE_H
#define TINTO_STATENODE_H


#include "Node.h"

namespace tinto {

    class _State {
        _State(const std::string &state, Node *node) : state(state), node(node) { }

        std::string state;
        Node *node;

        friend class StateNode;
    };

    class StateNode : public Node {
    public:
        StateNode(GameEngine *engine) : Node(engine) { }

        void addState(std::string state, Node *node);

        void setState(std::string state);

        std::vector<_State> states;
    };

}


#endif //TINTO_STATENODE_H
