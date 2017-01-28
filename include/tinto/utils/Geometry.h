//
//  GRect.hpp
//  WheelOfFortune
//
//  Created by Bruno Fortunato on 20/05/16.
//  Copyright © 2016 Bruno Fortunato. All rights reserved.
//

#ifndef Geometry_h
#define Geometry_h

#include <SDL.h>

namespace tinto {

    class GPoint {
    public:
        GPoint(float x, float y) : x(x), y(y) { }

        GPoint() { }

        SDL_Point toSDL();

        float x = 0;
        float y = 0;

        void translate(float x, float y);

        void rotate(GPoint origin, float angle);
    };

    class GSize {
    public:
        GSize() { }

        GSize(float width, float height) : width(width), height(height) { }

        float width = 0;
        float height = 0;
    };

    class GRect {
    public:
        GRect() { }

        GRect(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) { }

        float width = 0;
        float height = 0;
        float x = 0;
        float y = 0;

        SDL_Rect toSDL();

        GPoint getCenter();

        bool isEmpty();

        static GRect make(float x, float y, float w, float h);

        void translate(float x, float y);

        float getRight();

        float getBottom();

        void scale(float x, float y);

        bool contains(GPoint point);
    };

}


#endif /* Geometry_h */
