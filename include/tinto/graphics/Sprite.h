//
//  Sprite.h
//  WheelOfFortune
//
//  Created by Bruno Fortunato on 20/05/16.
//  Copyright © 2016 Bruno Fortunato. All rights reserved.
//

#ifndef Sprite_h
#define Sprite_h

#include "Node.h"

namespace tinto {

    class Sprite : public Node {

    public:
        Sprite(GameEngine *engine);

        virtual void update(GameTime *gameTime) override;

        virtual void draw(GameTime *gameTime) override;

        virtual void destroy() override;

        virtual void load(std::string path);

        virtual void loadScaled(std::string path, std::string ext);

        GSize realSize;
        GRect srcRect;

        Flip flip = Flip::NONE;

        std::string name;

    private:
        SDL_Texture *_texture = nullptr;
        SDL_Surface *_surface = nullptr;
        bool _loadComplete = false;

        void completeLoad();
    };

}

#endif /* Sprite_h */
