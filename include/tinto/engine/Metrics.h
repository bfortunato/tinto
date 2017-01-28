//
// Created by Bruno Fortunato on 30/05/16.
//

#ifndef TINTO_METRICS_H
#define TINTO_METRICS_H


#include "tinto/utils/Geometry.h"
#include "GameEngine.h"

namespace tinto {

    class Metrics {
    public:
        Metrics(GameEngine *engine) : _engine(engine) { }

        GSize realSize;
        GSize logicalSize;
        GSize windowSize;

        float density;

        void init();

        GRect toReal(GRect logicalRect);

        GRect toLogical(GRect realRect);

        GPoint toReal(GPoint logicalPoint);

        GPoint toLogical(GPoint realPoint);

        GSize toReal(GSize logicalSize);

        GSize toLogical(GSize realSize);

        float ratio;
        GRect rect;

    private:
        GameEngine *_engine;
    };

}


#endif //TINTO_METRICS_H
