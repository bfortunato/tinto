//
// Created by Bruno Fortunato on 20/06/16.
//

#ifndef TINTO_SOUNDMANAGER_H
#define TINTO_SOUNDMANAGER_H


#include <string>
#include "Sound.h"
#include "tinto/utils/ObjectCollector.h"
#include "Music.h"

namespace tinto {

    class SoundManager : public Collectable {
    public:
        SoundManager(GameEngine *engine);

        ~SoundManager();

        void loadSound(std::string id, std::string path);

        void playSound(std::string id);

        void loadMusic(std::string id, std::string path, bool loop = false);

        void playMusic(std::string id);

        void stopMusic(std::string id);

        void destroy();

        GameEngine *engine;

    private:
        ObjectCollector *collector;
        std::vector<Sound *> *_sounds;
        std::vector<Music *> *_musics;

    };

}


#endif //TINTO_SOUNDMANAGER_H
