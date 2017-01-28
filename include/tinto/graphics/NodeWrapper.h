//
// Created by Bruno Fortunato on 06/06/16.
//

#ifndef TINTO_NODEWRAPPER_H
#define TINTO_NODEWRAPPER_H


#include "Node.h"

namespace tinto {

    class NodeWrapper : public Node {
    public:
        virtual void init() override;

        virtual void update(GameTime *gameTime) override;

        virtual void draw(GameTime *gameTime) override;

        NodeWrapper(GameEngine *engine, Node *wrapped) : Node(engine), _wrapped(wrapped) { }

    private:
        Node *_wrapped;
    };

}

#endif //TINTO_NODEWRAPPER_H
