//
//  Node.hpp
//  WheelOfFortune
//
//  Created by Bruno Fortunato on 20/05/16.
//  Copyright © 2016 Bruno Fortunato. All rights reserved.
//

#ifndef Node_h
#define Node_h

#include <iostream>
#include <vector>

#include "tinto/utils/Geometry.h"
#include "tinto/engine/GameTime.h"
#include "tinto/engine/GameEngine.h"
#include "tinto/anim/Animation.h"
#include "tinto/engine/Metrics.h"
#include "tinto/utils/Collectable.h"
#include "tinto/engine/Input.h"

namespace tinto {

    enum Flip {
        NONE = 0x00000000, /**< Do not flip */
                HORIZONTAL = 0x00000001, /**< flip horizontally */
                VERTICAL = 0x00000002     /**< flip vertically */
    };

    class Node : public Collectable, public Observable, public DispatchOwner {
    public:
        Node(GameEngine *engine);

        virtual ~Node();

        bool active = true;

        GRect rect;
        GPoint origin;

        float alpha = 1;
        float rotation = 0;
        float scaleX = 1;
        float scaleY = 1;

        std::string tag = "";

        std::vector<Node *> *children;
        Node *parent = nullptr;

        virtual void init();

        virtual void update(GameTime *gameTime);

        virtual void draw(GameTime *gameTime);

        virtual void destroy();

        float computedRotation();

        float computedScaleX();

        float computedScaleY();

        float computedX();

        float computedY();

        float computedAlpha();

        GRect computedRealRect();

        bool hitTest(GPoint p);

        void addChild(Node *child);

        void animate(AnimationProperty property, float from, float to, float duration,
                     AnimationEase ease = AnimationEase::EASE_NONE, bool loop = false);

        void animate(Animation *animation);

        void stopAnimations();

        void dispatch(std::string name, Function action);

        void dispatchDelayed(std::string name, Function action, float delay);

        void cancelDispatch();

    protected:
        GameEngine *engine;

        float computedLeft();

        float computedTop();

        GRect computedRect();

        std::vector<Node *> collectParents();
    };

}

#endif /* Node_h */
