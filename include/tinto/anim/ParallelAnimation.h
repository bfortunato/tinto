//
// Created by Bruno Fortunato on 23/05/16.
//

#ifndef TINTO_PARALLELANIMATION_H
#define TINTO_PARALLELANIMATION_H


#include <vector>
#include "Animation.h"
#include "tinto/engine/GameEngine.h"

namespace tinto {

    class ParallelAnimation : public Animation {
    public:
        ParallelAnimation() : Animation(nullptr) { }

        virtual ~ParallelAnimation() override;

        virtual void reset() override;

        virtual void step(GameTime *gameTime) override;

        virtual bool isComplete() override;

        void addChild(Animation *child);

        static ParallelAnimation *create(std::initializer_list<Animation *> animations, bool loop = false);

    private:
        std::vector<Animation *> children;
        int currentAnimationIndex;
    };

}

#endif //TINTO_PARALLELANIMATION_H
