//
// Created by Bruno Fortunato on 23/05/16.
//

#include "tinto/graphics/SpriteSheet.h"

namespace tinto {

    void SpriteSheet::update(GameTime *gameTime) {
        this->time += gameTime->getElapsedTime();
        index = (time / (1000 / fps)) % frames;
        float internalFrameWidth = 1.0 / (float) frames;
        srcRect.x = (float) index * internalFrameWidth;

        Sprite::update(gameTime);
    }

    void SpriteSheet::draw(GameTime *gameTime) {
        Sprite::draw(gameTime);
    }

    void SpriteSheet::load(std::string path) {
        Sprite::load(path);

        frameWidth = rect.width / (float) frames;
        rect.width = frameWidth;
        srcRect.width = 1.0 / (float) frames;
    }

}