//
// Created by Bruno Fortunato on 30/05/16.
//

#ifndef TINTO_AUDIO_H
#define TINTO_AUDIO_H

#include <iostream>
#include "tinto/engine/GameEngine.h"
#include "tinto/utils/Collectable.h"

namespace tinto {

    class Audio : public Collectable {
    public:
        Audio(GameEngine *engine) : engine(engine) { }

        virtual void load(std::string path);

        virtual void play();

        virtual void pause();

        virtual void stop();

        virtual void destroy();

        bool loop = false;
        std::string tag;

    protected:
        GameEngine *engine;

    };

}

#endif //TINTO_SOUNDEFFECT_H
