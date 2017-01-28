//
// Created by Bruno Fortunato on 21/05/16.
//

#include <iostream>
#include <vector>
#include <SDL_ttf.h>

#include "SDL_image.h"
#include "tinto/engine/GameEngine.h"
#include "tinto/engine/Metrics.h"
#include "tinto/scenes/SceneManager.h"
#include "tinto/engine/Input.h"
#include "tinto/utils/Thread.h"

namespace tinto {

    GameEngine::GameEngine() {
        animations = new std::vector<Animation *>();
        removableAnimations = new std::vector<Animation *>();
        dispatchList = new std::vector<Action *>();
        inDispatch_dispatchList = new std::vector<Action *>();
        delayedDispatchList = new std::vector<DelayedAction *>();
        inDispatch_delayedDispatchList = new std::vector<DelayedAction *>();
    }

    GameEngine::~GameEngine() {
        delete animations;
        delete removableAnimations;
        delete dispatchList;
        delete inDispatch_dispatchList;
        delete delayedDispatchList;
        delete inDispatch_delayedDispatchList;
    }

    void GameEngine::init(int width, int height) {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            SDL_Log("Error initializing SDL: %s", SDL_GetError());
            throw std::exception();
        }

        if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0) {
            SDL_Log("Error initializing SDL_image: %s", SDL_GetError());
            throw std::exception();
        }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
            SDL_Log("Error initializing audio: %s", SDL_GetError());
            throw std::exception();
        }

        if (TTF_Init() < 0) {
            SDL_Log("Error initializing ttf: %s", SDL_GetError());
            throw std::exception();
        }

        Thread::init();

        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    #ifdef DESKTOP
        bool fullscreen = width == 0 && height == 0;
        int flags = SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI;
        if (fullscreen) {
            flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        }

        window = SDL_CreateWindow(
                "WheelOfFortune",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                static_cast<int>(width),
                static_cast<int>(height),
                flags);
    #else //MOBILE
        window = SDL_CreateWindow(
                "WheelOfFortune",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                0,
                0,
    #if TARGET_OS_SIMULATOR
                SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
    #else
                SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALLOW_HIGHDPI);
    #endif
    #endif

        if (window == nullptr) {
            SDL_Log("Error initializing window: %s", SDL_GetError());
            throw std::exception();
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr) {
            SDL_Log("Error initializing renderer: %s", SDL_GetError());
            throw std::exception();
        }

        gameTime = new GameTime();

        metrics = new Metrics(this);
        metrics->init();

        sceneManager = new SceneManager(this);
        sceneManager->init();

        input = new Input(this);
        input->init();
    }


    void GameEngine::run() {
        std::vector<Animation *> removableAnimations;

        running = true;
        while (running) {
            gameTime->beginFrame();

            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderClear(renderer);

            this->executeDispatchAction();

            this->performAnimations();
            this->cleanAnimations();

            this->handleEvents();

            if (sceneManager != nullptr) {
                sceneManager->update(gameTime);
                sceneManager->draw(gameTime);
            }

            SDL_RenderPresent(renderer);

            this->input->cleanup();

            sceneManager->performChange();

            gameTime->endFrame();
            gameTime->delay();
            gameTime->step();
        }
    }


    void GameEngine::destroy() {
        delete gameTime; gameTime = nullptr;
        delete sceneManager; sceneManager = nullptr;

        SDL_DestroyRenderer(renderer); renderer = nullptr;
        SDL_DestroyWindow(window); window = nullptr;

        TTF_Quit();
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    void GameEngine::performAnimations() {
        for (auto it : *animations) {
            if (it->canceled) {
                removableAnimations->push_back(it);
            } else {
                it->step(gameTime);
                if (it->isComplete()) {
                    removableAnimations->push_back(it);
                }
            }
        }
    }

    void GameEngine::cleanAnimations() {
        for (auto it : *removableAnimations) {
            animations->erase(std::find(animations->begin(), animations->end(), it));
            delete it;
        }

        removableAnimations->clear();
    }

    void GameEngine::addAnimation(Animation *animation) {
        animations->push_back(animation);
    }


    void GameEngine::dispatch(DispatchOwner *owner, std::string name, Function action) {
        if (_dispatching) {
            inDispatch_dispatchList->push_back(new Action(owner, name, action));
        } else {
            dispatchList->push_back(new Action(owner, name, action));
        }
    }

    void GameEngine::dispatchDelayed(DispatchOwner *owner, std::string name, Function action, float delay) {
        if (_dispatching) {
            inDispatch_delayedDispatchList->push_back(new DelayedAction(owner, name, action, delay));
        } else {
            delayedDispatchList->push_back(new DelayedAction(owner, name, action, delay));
        }
    }

    void GameEngine::executeDispatchAction() {
        _dispatching = true;
        for (auto act : *dispatchList) {
            if (act->canceled) {
                SDL_Log("Action canceled: %s", act->name.c_str());
            } else {
                SDL_Log("Executing action %s", act->name.c_str());

                act->action();
            }

            delete act;
        }

        dispatchList->clear();

        std::vector<DelayedAction *> removable;
        for (auto act : *delayedDispatchList) {
            if ((SDL_GetTicks() - act->start) >= act->delay) {
                if (act->canceled) {
                    SDL_Log("Delayed action canceled: %s", act->name.c_str());
                } else {
                    SDL_Log("Executing delayed action %s", act->name.c_str());

                    act->action();
                }
                removable.push_back(act);
            }
        }

        for (auto a : removable) {
            delayedDispatchList->erase(std::find(delayedDispatchList->begin(), delayedDispatchList->end(), a));
            delete a;
        }

        for (auto d : *inDispatch_dispatchList) {
            dispatchList->push_back(d);
        }

        for (auto d: *inDispatch_delayedDispatchList) {
            delayedDispatchList->push_back(d);
        }

        inDispatch_dispatchList->clear();
        inDispatch_delayedDispatchList->clear();

        _dispatching = false;
    }

    void GameEngine::cancelDispatchByOwner(DispatchOwner *owner) {
        if (_dispatching) {
            SDL_Log("Cannot clean while dispatching");
            throw std::exception();
        }

        for (auto act : *dispatchList) {
            if (act->owner == owner) {
                SDL_Log("Canceling dispatch action %s", act->name.c_str());
                act->canceled = true;
            }
        }

        for (auto act : *inDispatch_dispatchList) {
            if (act->owner == owner) {
                SDL_Log("Canceling dispatch action %s", act->name.c_str());
                act->canceled = true;
            }
        }


        for (auto act : *delayedDispatchList) {
            if (act->owner == owner) {
                SDL_Log("Clean dispatch delayed action %s", act->name.c_str());

                act->canceled = true;
            }
        }

        for (auto act : *inDispatch_delayedDispatchList) {
            if (act->owner == owner) {
                SDL_Log("Clean dispatch delayed action %s", act->name.c_str());

                act->canceled = true;
            }
        }

    }


    void GameEngine::handleEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else {
                input->handle(&event);
            }
        }
    }

    void GameEngine::stopAnimations(Node *node) {
        for (auto animation : *animations) {
            if (animation->target == node) {
                animation->cancel();
            }
        }
    }


}



