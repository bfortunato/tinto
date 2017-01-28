//
//  Node.cpp
//  WheelOfFortune
//
//  Created by Bruno Fortunato on 20/05/16.
//  Copyright © 2016 Bruno Fortunato. All rights reserved.
//

#include "tinto/graphics/Node.h"

namespace tinto {

    Node::Node(GameEngine *engine) : Collectable(), engine(engine) {
        origin.x = 0.5;
        origin.y = 0.5;

        children = new std::vector<Node *>();
    }

    Node::~Node() {
        delete children;
    }

    void Node::init() { }

    void Node::update(GameTime *gameTime) {
        if (!active) {
            return;
        }

        for (auto child : *children) {
            child->update(gameTime);
        }
    }

    void Node::draw(GameTime *gameTime) {
        if (!active) {
            return;
        }

        for (auto child : *children) {
            child->draw(gameTime);
        }
    }

    void Node::destroy() {
        for (auto child : *children) {
            child->destroy();
        }
    }

    float Node::computedRotation() {
        float rot = this->rotation;
        if (this->parent != nullptr) {
            rot += this->parent->computedRotation();
        }

        return rot;
    }

    float Node::computedScaleX() {
        float sx = this->scaleX;
        if (this->parent != nullptr) {
            sx *= this->parent->computedScaleX();
        }

        return sx;
    }

    float Node::computedScaleY() {
        float sy = this->scaleY;
        if (this->parent != nullptr) {
            sy *= this->parent->computedScaleY();
        }

        return sy;
    }

    float Node::computedAlpha() {
        float alpha = this->alpha;
        if (this->parent != nullptr) {
            alpha *= this->parent->computedAlpha();
        }

        return alpha;
    }

    float Node::computedX() {
        float x = this->rect.x;
        if (this->parent != nullptr) {
            x += this->parent->computedX();
        }

        return x;
    }

    float Node::computedY() {
        float y = this->rect.y;
        if (this->parent != nullptr) {
            y += this->parent->computedY();
        }

        return y;
    }

    void Node::addChild(Node *child) {
        child->parent = this;
        children->push_back(child);
    }

    void Node::animate(AnimationProperty property, float from, float to, float duration, AnimationEase ease,
                       bool loop) {
        auto anim = new Animation(this);
        anim->property = property;
        anim->from = from;
        anim->to = to;
        anim->duration = duration;
        anim->ease = ease;
        anim->loop = loop;

        engine->addAnimation(anim);
    }

    void Node::animate(Animation *animation) {
        animation->target = this;
        engine->addAnimation(animation);
    }

    GRect Node::computedRect() {
        if (parent == nullptr) {
            return rect;
        }
        //if parent is scaled, needs to scale x and y
        float inParentX = rect.x * fabsf(parent->computedScaleX());
        float inParentY = rect.y * fabsf(parent->computedScaleY());

        //scale points
        float scaledWidth = rect.width * fabsf(computedScaleX());
        float scaledHeight = rect.height * fabsf(computedScaleY());
        float scaledX = inParentX - (scaledWidth * origin.x);
        float scaledY = inParentY - (scaledHeight * origin.y);

        GRect computedRect = GRect(scaledX, scaledY, scaledWidth, scaledHeight);

        GRect parentRect = parent->computedRect();

        computedRect.translate(parentRect.x, parentRect.y);

        return computedRect;
    }

    GRect Node::computedRealRect() {
        GRect workingRect = computedRect();
        if (parent != nullptr) {

            Node *theParent = parent;

            std::vector<Node *> parents = collectParents();

            for (Node *parent : parents) {
                GPoint center = workingRect.getCenter();

                //rotate for parent
                GRect parentWorkingRect = parent->computedRect();

                GPoint parentRotationOrigin(parentWorkingRect.width * parent->origin.x,
                                            parentWorkingRect.height * parent->origin.y);
                parentRotationOrigin.translate(parentWorkingRect.x, parentWorkingRect.y);

                GPoint centerRotatedInParent(center.x, center.y);
                centerRotatedInParent.rotate(parentRotationOrigin, parent->rotation);

                GPoint parentDelta(centerRotatedInParent.x - center.x, centerRotatedInParent.y - center.y);
                workingRect.translate(parentDelta.x, parentDelta.y);
            }


            //rotate myself
            GPoint center = workingRect.getCenter();

            GPoint rotationOrigin(workingRect.width * origin.x, workingRect.height * origin.y);
            rotationOrigin.translate(workingRect.x, workingRect.y);

            GPoint rotatedCenter(center.x, center.y);
            rotatedCenter.rotate(rotationOrigin, rotation);

            GPoint delta(rotatedCenter.x - center.x, rotatedCenter.y - center.y);
            workingRect.translate(delta.x, delta.y);
        }

        GRect realRect = engine->metrics->toReal(workingRect);

        return realRect;
    }

    bool Node::hitTest(GPoint p) {
        GPoint rp = engine->metrics->toReal(p);
        GRect rr = computedRealRect();
        float r = computedRotation() * -1; //inverse rotate point to check instead of rotate rect

        rp.rotate(GPoint(), r);

        return rr.contains(rp);
    }

    float Node::computedLeft() {
        return rect.x - (rect.width * origin.x);
    }

    float Node::computedTop() {
        return rect.y - (rect.height * origin.y);
    }

    void Node::stopAnimations() {
        engine->stopAnimations(this);
    }


    void Node::dispatch(std::string name, Function action) {
        engine->dispatch(this, name, action);
    }


    void Node::dispatchDelayed(std::string name, Function action, float delay) {
        engine->dispatchDelayed(this, name, action, delay);
    }

    void Node::cancelDispatch() {
        engine->cancelDispatchByOwner(this);
    }

    std::vector<Node *> Node::collectParents() {
        auto parents = std::vector<Node *>();
        Node *p = parent;
        while (p != nullptr) {
            parents.insert(parents.begin(), p);
            p = p->parent;
        }

        return parents;
    }

}




