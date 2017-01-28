//
// Created by Bruno Fortunato on 30/05/16.
//

#ifndef TINTO_MUSIC_H
#define TINTO_MUSIC_H


#include <SDL_mixer.h>
#include "Audio.h"

namespace tinto {

    class Music : public Audio {
    public:
        Music(GameEngine *engine) : Audio(engine) {
            loop = true;
        }

        virtual void load(std::string path) override;

        virtual void play() override;

        virtual void pause() override;

        virtual void stop() override;

        virtual void destroy() override;

    private:
        Mix_Music *_music = nullptr;

    };

}


#endif //TINTO_MUSIC_H
