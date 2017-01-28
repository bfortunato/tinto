//
// Created by Bruno Fortunato on 01/06/16.
//

#include "tinto/scenes/Scene.h"
#include "tinto/utils/Thread.h"

namespace tinto {

    Scene::Scene(GameEngine *engine) : Node(engine) {
        collector = new ObjectCollector();
    }

    Scene::~Scene() {
        delete collector;
    }

    void Scene::preInit() {

    }

    void Scene::init() {
        Thread::checkMainThread();

        origin = GPoint(0, 0);
        rect = engine->metrics->rect;

        Node::init();
    }

    void Scene::update(GameTime *gameTime) {
        Thread::checkMainThread();

        Node::update(gameTime);
    }

    void Scene::draw(GameTime *gameTime) {
        Thread::checkMainThread();

        Node::draw(gameTime);
    }

    void Scene::destroy() {
        Thread::checkMainThread();

        Node::destroy();
    }

    void Scene::start() {
        stopped = false;
    }

    void __doStop(Node *node) {
        node->stopAnimations();
        node->cancelDispatch();

        for (auto child : *(node->children)) {
            __doStop(child);
        }
    }

    void Scene::stop() {
        for (auto child : *children) {
            __doStop(child);
        }

        __doStop(this);

        stopped = true;
    }

}








