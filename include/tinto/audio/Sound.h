//
// Created by Bruno Fortunato on 30/05/16.
//

#ifndef TINTO_SOUND_H
#define TINTO_SOUND_H


#include <SDL_mixer.h>
#include "Audio.h"

namespace tinto {

    class Sound : public Audio {
    public:
        Sound(GameEngine *engine) : Audio(engine) {
            _channel = -1;
        }

        virtual void load(std::string path) override;

        virtual void play() override;

        virtual void pause() override;

        virtual void stop() override;

        virtual void destroy() override;

    private:
        Mix_Chunk *_chunk;
        int _channel;
    };

}

#endif //TINTO_SOUND_H
