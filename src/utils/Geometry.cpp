//
//  GRect.cpp
//  WheelOfFortune
//
//  Created by Bruno Fortunato on 20/05/16.
//  Copyright © 2016 Bruno Fortunato. All rights reserved.
//

#include "tinto/utils/Geometry.h"

namespace tinto {

    SDL_Rect GRect::toSDL() {
        SDL_Rect rect = {static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height)};
        return rect;
    }

    GRect GRect::make(float x, float y, float w, float h) {
        GRect g;
        g.x = x;
        g.y = y;
        g.width = w;
        g.height = h;
        return g;
    }

    GPoint GRect::getCenter() {
        GPoint center;
        center.x = x + width / 2;
        center.y = y + height / 2;
        return center;
    }

    bool GRect::isEmpty() {
        return x == 0 && y == 0 && width == 0 && height == 0;
    }

    void GRect::translate(float x, float y) {
        this->x += x;
        this->y += y;
    }

    float GRect::getRight() {
        return x + width;
    }


    float GRect::getBottom() {
        return y + height;
    }

    void GRect::scale(float x, float y) {
        this->width *= x;
        this->height *= y;
    }

    bool GRect::contains(GPoint point) {
        return point.x >= x && point.x <= getRight() &&
               point.y >= y && point.y <= getBottom();
    }


    SDL_Point GPoint::toSDL() {
        return {static_cast<int>(x), static_cast<int>(y)};
    }

    void GPoint::translate(float x, float y) {
        this->x += x;
        this->y += y;
    }

    void GPoint::rotate(GPoint origin, float angle) {
        float radians = angle * M_PI / 180;
        float cs = (float) cos(radians);
        float sn = (float) sin(radians);

        GPoint rotated;
        rotated.x = cs * (x - origin.x) - sn * (y - origin.y) + origin.x;
        rotated.y = sn * (x - origin.x) + cs * (y - origin.y) + origin.y;

        this->x = rotated.x;
        this->y = rotated.y;
    }

}




