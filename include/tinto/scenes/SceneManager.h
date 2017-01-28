//
// Created by Bruno Fortunato on 01/06/16.
//

#ifndef TINTO_SCENEMANAGER_H
#define TINTO_SCENEMANAGER_H

#include "Scene.h"

namespace tinto {

    enum Transition {
        TRANSITION_NONE,
        TRANSITION_FADE,
        TRANSITION_SLIDE_LEFT,
        TRANSITION_SLIDE_RIGHT
    };

    class SceneManager : public Node {
    public:
        SceneManager(GameEngine *engine) : Node(engine) { }

        virtual void init() override;

        virtual void update(GameTime *gameTime) override;

        virtual void draw(GameTime *gameTime) override;

        virtual void destroy() override;

        void setRoot(Scene *scene);

        void change(Scene *scene, Transition transition = Transition::TRANSITION_NONE);

        void performChange();

    private:
        Uint32 _transitionDuration = 1000;
        Scene *_backScene = nullptr;
        Scene *_frontScene = nullptr;

        void cleanScene(Scene *tmp);

        Scene *_nextScene = nullptr;
        Transition _nextTransition;
    };

}


#endif //TINTO_SCENEMANAGER_H
