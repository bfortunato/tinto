//
// Created by Bruno Fortunato on 22/05/16.
//

#ifndef TINTO_COLOR_H
#define TINTO_COLOR_H


#include <SDL.h>

namespace tinto {

    class Color {
    public:
        Color() { }

        Color(int r, int g, int b) : r(r), g(g), b(b) { }

        Color(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) { }

        Color(int hex);

        int r = 0, g = 0, b = 0, a = 0xFF;

        SDL_Color toSDL();
    };

}


#endif //TINTO_COLOR_H
