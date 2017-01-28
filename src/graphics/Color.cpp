//
// Created by Bruno Fortunato on 22/05/16.
//

#include "tinto/graphics/Color.h"

namespace tinto {

    SDL_Color Color::toSDL() {
        return {static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b), static_cast<Uint8>(a)};
    }

    Color::Color(int hex) {
        r = static_cast<int>(((hex >> 24) & 0xFF));
        g = static_cast<int>(((hex >> 16) & 0xFF));
        b = static_cast<int>(((hex >> 8) & 0xFF));
        a = static_cast<int>(((hex) & 0xFF));
    }

}

