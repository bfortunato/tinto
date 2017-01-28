//
// Created by Bruno Fortunato on 31/05/16.
//

#ifndef TINTO_TEXT_H
#define TINTO_TEXT_H

#include <SDL_ttf.h>

#include "Node.h"
#include "Color.h"

namespace tinto {

    class Text : public Node {

    public:
        Text(GameEngine *engine);

        ~Text();

        virtual void destroy() override;

        virtual void draw(GameTime *gameTime) override;

        void loadFont(std::string path, int size);

        void invalidate();

        std::string text = "";
        Color textColor = Color(0xFF, 0xFF, 0xFF);
        Flip flip = Flip::NONE;

        bool dropShadow = true;

    private:
        TTF_Font *_font = nullptr;
        GSize _size;
        SDL_Texture *_texture = nullptr;
        SDL_Texture *_shadowTexture = nullptr;
    };

}

#endif //TINTO_TEXT_H
