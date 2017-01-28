//
// Created by Bruno Fortunato on 20/05/16.
//

#ifndef TINTO_RECTANGLE_H
#define TINTO_RECTANGLE_H

#include "Color.h"
#include "Drawable.h"

namespace tinto {

    class Rectangle : public Drawable {
    public:
        Rectangle(GameEngine *engine) : Drawable(engine) { }

        Color backgroundColor;

    protected:
        virtual void paint(GameTime *gameTime, GRect *realRect) override;

    private:
        SDL_Texture *_texture;

    };

}


#endif //TINTO_RECTANGLE_H
