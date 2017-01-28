//
// Created by Bruno Fortunato on 23/05/16.
//

#ifndef TINTO_SPRITESHEET_H
#define TINTO_SPRITESHEET_H


#include "Node.h"
#include "Sprite.h"

namespace tinto {

    class SpriteSheet : public Sprite {
    public:
        virtual void update(GameTime *gameTime) override;

        virtual void draw(GameTime *gameTime) override;

        virtual void load(std::string path) override;

        SpriteSheet(GameEngine *engine, Uint32 frames) : Sprite(engine), frames(frames) { }

        short fps = 60;
    private:
        unsigned int index = 0;
        float frameWidth;
        Uint32 frames = 0;
        Uint32 time;
    };

}

#endif //TINTO_SPRITESHEET_H
