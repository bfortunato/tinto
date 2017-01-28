//
// Created by Bruno Fortunato on 20/05/16.
//

#ifndef TINTO_TIME_H
#define TINTO_TIME_H

namespace tinto {

    class GameTime {
    public:
        Uint32 getTotalTime();

        Uint32 getElapsedTime();

        float getElapsedTimeF();

        void delay();

        void step();

        void beginFrame();

        void endFrame();

        float calculateFrameRate();

    private:
        Uint32 frameBeginTime;
        Uint32 computationTime;


        Uint32 lastUpdateTime;


        Uint32 elapsedTime;
    };

}

#endif //TINTO_TIME_H
