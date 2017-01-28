//
// Created by Bruno Fortunato on 21/05/16.
//

#ifndef TINTO_GAMEENGINE_H
#define TINTO_GAMEENGINE_H


#include <vector>
#include <iostream>
#include <thread>
#include <functional>
#include <list>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "GameTime.h"
#include "tinto/utils/Geometry.h"
#include "tinto/anim/Animation.h"

namespace tinto {

    class SceneManager;

    class Metrics;

    class Input;

#define RAND (static_cast<float>(rand() % 1000) / 1000.0f)

    typedef std::function<void()> Function;

    class DispatchOwner {

    };

    class Action {
    public:
        Action(DispatchOwner *owner, std::string name, Function action) : owner(owner), name(name), action(action) { };

        DispatchOwner *owner;
        std::string name;
        Function action;
        bool canceled = false;
    };

    class DelayedAction : public Action {
    public:
        DelayedAction(DispatchOwner *owner, std::string name, Function action, float delay) : Action(owner, name,
                                                                                                     action),
                                                                                              delay(delay) {
            start = SDL_GetTicks();
        };

        float delay = 0;
        Uint32 start;
    };

    class GameEngine {
    private:
        bool running;
        std::vector<Animation *> *animations;
        std::vector<Animation *> *removableAnimations;
        std::vector<Action *> *dispatchList;
        std::vector<Action *> *inDispatch_dispatchList;
        std::vector<DelayedAction *> *delayedDispatchList;
        std::vector<DelayedAction *> *inDispatch_delayedDispatchList;
        bool _dispatching = false;

    public:
        GameEngine();

        ~GameEngine();

        SDL_Window *window;
        SDL_Renderer *renderer;

        SceneManager *sceneManager;
        GameTime *gameTime;
        Metrics *metrics;
        Input *input;

        void init(int width = 0, int height = 0);

        void run();

        void destroy();

        void addAnimation(Animation *animation);

        void performAnimations();

        void cleanAnimations();

        void stopAnimations(Node *node);

        void dispatch(DispatchOwner *owner, std::string name, Function action);

        void dispatchDelayed(DispatchOwner *owner, std::string name, Function action, float delay);

        void executeDispatchAction();

        void cancelDispatchByOwner(DispatchOwner *owner);

        void handleEvents();
    };

}

#endif //TINTO_GAMEENGINE_H
