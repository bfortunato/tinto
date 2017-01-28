//
// Created by Bruno Fortunato on 20/05/16.
//

#include <exception>

#include "tinto/graphics/Rectangle.h"

namespace tinto {

    void Rectangle::paint(GameTime *gameTime, GRect *realRect) {
        Drawable::paint(gameTime, realRect);

        SDL_Rect sdlRect = realRect->toSDL();
        SDL_SetRenderDrawColor(engine->renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b,
                               backgroundColor.a);
        SDL_RenderFillRect(engine->renderer, &sdlRect);
    }

}


