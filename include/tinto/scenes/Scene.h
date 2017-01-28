//
// Created by Bruno Fortunato on 01/06/16.
//

#ifndef TINTO_SCENE_H
#define TINTO_SCENE_H


#include "tinto/graphics/Node.h"
#include "tinto/utils/ObjectCollector.h"

namespace tinto {

    class Scene : public Node {
    public:
        Scene(GameEngine *engine);

        virtual ~Scene();

        virtual void preInit();

        virtual void init() override;

        virtual void update(GameTime *gameTime) override;

        virtual void draw(GameTime *gameTime) override;

        virtual void destroy() override;

        virtual void start();

        virtual void stop();

        bool stopped = false;
    protected:
        ObjectCollector *collector;

    };

}

#endif //TINTO_SCENE_H
