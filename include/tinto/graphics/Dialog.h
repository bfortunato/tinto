//
// Created by Bruno Fortunato on 20/06/16.
//

#ifndef TINTO_DIALOG_H
#define TINTO_DIALOG_H


#include "Node.h"

namespace tinto {

    class Dialog : public Node {
    public:
        virtual void init() override;

        Dialog(GameEngine *engine) : Node(engine) { }

        Node *background = nullptr;

        void show();

        void hide();
    };

}

#endif //TINTO_DIALOG_H
