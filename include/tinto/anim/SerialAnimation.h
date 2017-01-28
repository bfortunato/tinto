//
// Created by Bruno Fortunato on 23/05/16.
//

#ifndef TINTO_SERIALANIMATION_H
#define TINTO_SERIALANIMATION_H


#include <vector>
#include "Animation.h"
#include "tinto/engine/GameEngine.h"

namespace tinto {

    class SerialAnimation : public Animation {
    public:
        SerialAnimation() : Animation(nullptr) { }

        virtual ~SerialAnimation() override;

        virtual void reset() override;

        virtual void step(GameTime *gameTime) override;

        virtual bool isComplete() override;

        void addChild(Animation *child);

        static SerialAnimation *create(std::initializer_list<Animation *> animations, bool loop = false);

    private:
        std::vector<Animation *> children;
        int currentAnimationIndex;
    };

}

#endif //TINTO_SERIALANIMATION_H
