//
// Created by Bruno Fortunato on 30/05/16.
//

#include <SDL.h>

#include "tinto/engine/Metrics.h"

#define METRICS_1 800
#define METRICS_2 1280
#define METRICS_3 1920

#define LOGICAL_SIZE 10.0f

namespace tinto {

    void Metrics::init() {
        int drawableWidth;
        int drawableHeight;
        int windowWidth;
        int windowHeight;

        SDL_GetWindowSize(_engine->window, &windowWidth, &windowHeight);
        SDL_GL_GetDrawableSize(_engine->window, &drawableWidth, &drawableHeight);

        float size = std::max(drawableWidth, drawableHeight);

        realSize.width = drawableWidth;
        realSize.height = drawableHeight;

        windowSize.width = windowWidth;
        windowSize.height = windowHeight;

        this->density = drawableHeight / windowHeight;
        if (drawableHeight <= METRICS_1) {
            density = 1;
        } else if (drawableHeight > METRICS_1 && drawableHeight <= METRICS_2) {
            density = 2;
        } else if (drawableHeight > METRICS_2 && drawableHeight <= METRICS_3) {
            density = 3;
        } else if (drawableHeight > METRICS_3) {
            density = 4;
        }

        this->ratio = size / LOGICAL_SIZE;

        this->logicalSize.width = realSize.width / ratio;
        this->logicalSize.height = realSize.height / ratio;

        this->rect = GRect(0, 0, this->logicalSize.width, this->logicalSize.height);
    }

    GRect Metrics::toReal(GRect logicalRect) {
        return {logicalRect.x * ratio, logicalRect.y * ratio, logicalRect.width * ratio, logicalRect.height * ratio};
    }

    GRect Metrics::toLogical(GRect realRect) {
        GRect logicalRect = {realRect.x / ratio, realRect.y / ratio, realRect.width / ratio, realRect.height / ratio};
        return logicalRect;
    }

    GPoint Metrics::toReal(GPoint logicalPoint) {
        return {logicalPoint.x * ratio, logicalPoint.y * ratio};
    }

    GPoint Metrics::toLogical(GPoint realPoint) {
        GPoint logicalPoint = {realPoint.x / ratio, realPoint.y / ratio};
        return logicalPoint;
    }

    GSize Metrics::toReal(GSize logicalSize) {
        return {logicalSize.width * ratio, logicalSize.height * ratio};
    }

    GSize Metrics::toLogical(GSize realSize) {
        return {realSize.width / ratio, realSize.height / ratio};
    }

}

