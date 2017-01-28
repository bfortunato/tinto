//
// Created by Bruno Fortunato on 20/06/16.
//

#include "tinto/audio/SoundManager.h"

namespace tinto {

    SoundManager::SoundManager(GameEngine *engine) : engine(engine) {
        collector = new ObjectCollector();
        _sounds = new std::vector<Sound *>();
        _musics = new std::vector<Music *>();
    }

    SoundManager::~SoundManager() {
        delete collector;
        delete _sounds;
        delete _musics;
    }


    void SoundManager::loadSound(std::string id, std::string path) {
        auto sound = collector->collect(new Sound(engine));
        sound->load(path);
        sound->tag = id;
        _sounds->push_back(sound);
    }

    void SoundManager::playSound(std::string id) {
        for (auto sound : *_sounds) {
            if (sound->tag == id) {
                sound->play();
                return;
            }
        }

        SDL_Log("Sound not found: %s", id.c_str());
    }

    void SoundManager::loadMusic(std::string id, std::string path, bool loop) {
        auto music = collector->collect(new Music(engine));
        music->load(path);
        music->tag = id;
        music->loop = loop;
        _musics->push_back(music);
    }

    void SoundManager::playMusic(std::string id) {
        for (auto music : *_musics) {
            if (music->tag == id) {
                music->play();
                return;
            }
        }

        SDL_Log("Music not found: %s", id.c_str());
    }

    void SoundManager::stopMusic(std::string id) {
        for (auto music : *_musics) {
            if (music->tag == id) {
                music->stop();
                return;
            }
        }

        SDL_Log("Music not found: %s", id.c_str());
    }

    void SoundManager::destroy() {
        for (auto sound : *_sounds) {
            sound->destroy();
        }

        for (auto music : *_musics) {
            music->destroy();
        }
    }

}
