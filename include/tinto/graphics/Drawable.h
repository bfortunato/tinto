//
// Created by Bruno Fortunato on 14/06/16.
//

#ifndef TINTO_DRAWABLE_H
#define TINTO_DRAWABLE_H


#include "Node.h"

namespace tinto {

    class Drawable : public Node {
    public:
        Drawable(GameEngine *engine) : Node(engine) { }

        virtual void init() override;

        virtual void update(GameTime *gameTime) override;

        virtual void draw(GameTime *gameTime) override;

        virtual void destroy() override;

    protected:
        virtual void paint(GameTime *gameTime, GRect *realRect);

        SDL_Texture *_texture = nullptr;

    };

}

#endif //TINTO_DRAWABLE_H
