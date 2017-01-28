//
// Created by Bruno Fortunato on 01/06/16.
//

#include <SDL.h>

#include "tinto/scenes/SceneManager.h"
#include "tinto/graphics/FpsText.h"
#include "tinto/utils/Thread.h"

namespace tinto {

    void SceneManager::init() {
        Node::init();
        /*
        auto fpsText = new FpsText(engine);
        fpsText->loadFont("res/fonts/Roboto-Medium.ttf", static_cast<Uint8>(18 * engine->metrics->density));
        fpsText->alpha = 0.5;
        fpsText->rect.x = engine->metrics->rect.getRight() - 0.1f;
        fpsText->rect.y = 0.1;
        fpsText->origin = GPoint(1, 0);

        addChild(fpsText);
        */
    }

    void SceneManager::update(GameTime *gameTime) {
        Thread::checkMainThread();

        if (_backScene != nullptr) {
            _backScene->update(gameTime);
        }

        if (_frontScene != nullptr) {
            _frontScene->update(gameTime);
        }

        Node::update(gameTime);
    }

    void SceneManager::draw(GameTime *gameTime) {
        Thread::checkMainThread();

        if (_backScene != nullptr) {
            _backScene->draw(gameTime);
        }

        if (_frontScene != nullptr) {
            _frontScene->draw(gameTime);
        }

        Node::draw(gameTime);
    }

    void SceneManager::destroy() {
        Node::destroy();
    }


    void SceneManager::setRoot(Scene *scene) {
        if (_backScene != nullptr) {
            cleanScene(_backScene);
            _backScene = nullptr;
        }

        _frontScene = nullptr;

        scene->init();

        _frontScene = scene;
        _frontScene->start();
    }

    void SceneManager::change(Scene *scene, Transition transition) {
        _nextScene = scene;
        _nextTransition = transition;
    }

    void SceneManager::performChange() {
        if (_nextScene == nullptr) {
            return;
        }
        Scene *toClean = _frontScene;
        Scene *toChange = _nextScene;
        _nextScene = nullptr;

        _frontScene = nullptr;
        toChange->init();

        _frontScene = toChange;
        _frontScene->start();

        cleanScene(toClean);

        /*
    transition = TRANSITION_NONE;

    Scene *toClean = _frontScene;

    _frontScene = nullptr;

    scene->init();

    _frontScene = scene;
    _frontScene->start();

    switch (transition) {
        case TRANSITION_NONE:
            _backScene = nullptr;
            cleanScene(toClean);
            break;
        case TRANSITION_FADE:
            _frontScene->animate(AnimationProperty::ALPHA, 0, 1, _transitionDuration, AnimationEase::EASE_OUT);
            dispatchDelayed("scenemanager:change:transition_fade:cleanScene", [this, toClean]() { _backScene = nullptr; cleanScene(toClean); }, _transitionDuration);
            break;
        case TRANSITION_SLIDE_LEFT:
            _frontScene->animate(AnimationProperty::X, engine->metrics->rect.getRight(), engine->metrics->rect.x, _transitionDuration, AnimationEase::EASE_OUT);
            dispatchDelayed("scenemanager:change:transition_slide_left:cleanScene", [this, toClean]() { _backScene = nullptr; cleanScene(toClean); }, _transitionDuration);
            break;
        case TRANSITION_SLIDE_RIGHT:
            _frontScene->animate(AnimationProperty::X, engine->metrics->rect.x - engine->metrics->rect.width, engine->metrics->rect.x, _transitionDuration, AnimationEase::EASE_OUT);
            dispatchDelayed("scenemanager:change:transition_slide_right:cleanScene", [this, toClean]() { _backScene = nullptr; cleanScene(toClean); }, _transitionDuration);
            break;
    }*/
    }

    void SceneManager::cleanScene(Scene *tmp) {
        if (tmp != nullptr) {
            tmp->stop();
            tmp->destroy();
            delete tmp;
        }
    }

}