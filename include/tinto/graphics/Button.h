//
// Created by Bruno Fortunato on 03/06/16.
//

#ifndef TINTO_BUTTON_H
#define TINTO_BUTTON_H


#include "Node.h"

namespace tinto {

    enum ButtonState {
        BUTTON_STATE_NORMAL,
        BUTTON_STATE_PUSHED
    };

    class Button : public Node {
    public:
        Button(GameEngine *engine) : Node(engine) {
            SDL_Log("Button instanziated");
        }

        virtual ~Button() override {
            SDL_Log("Button destroyed");
        }


        virtual void update(GameTime *gameTime) override;

        virtual void draw(GameTime *gameTime) override;

        void setBackgroundNode(Node *background);

        void setNormalStateNode(Node *normalState);

        void setPushedStateNode(Node *pushedState);

        ButtonState state = BUTTON_STATE_NORMAL;

    protected:
        Node *_backgroundNode = nullptr;
        Node *_normalStateNode = nullptr;
        Node *_pushedStateNode = nullptr;
    };

}


#endif //TINTO_BUTTON_H
