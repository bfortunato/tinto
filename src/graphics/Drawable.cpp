//
// Created by Bruno Fortunato on 14/06/16.
//

#include "tinto/graphics/Drawable.h"

namespace tinto {

    void Drawable::init() {
        Node::init();

        _texture = SDL_CreateTexture(engine->renderer,
                                     SDL_PIXELFORMAT_RGBA8888,
                                     SDL_TEXTUREACCESS_TARGET,
                                     static_cast<Uint32>(engine->metrics->realSize.width),
                                     static_cast<Uint32>(engine->metrics->realSize.height)
        );

        if (_texture == nullptr) {
            SDL_Log("Cannot create texture: %s", SDL_GetError());
            throw std::exception();
        }
    }

    void Drawable::update(GameTime *gameTime) {
        Node::update(gameTime);
    }

    void Drawable::draw(GameTime *gameTime) {
        if (!active) {
            return;
        }

        if (_texture == nullptr) {
            return;
        }

        SDL_SetRenderTarget(engine->renderer, _texture);
        SDL_SetTextureBlendMode(_texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(_texture, static_cast<Uint8>(this->alpha * 255.0f));
        SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, 0);
        SDL_RenderClear(engine->renderer);

        GRect realRect = this->computedRealRect();
        GPoint transformOrigin(realRect.width * 0.5f, realRect.height * 0.5f);

        SDL_Rect sdlRect = realRect.toSDL();
        SDL_Point sdlTransformOrigin = transformOrigin.toSDL();

        paint(gameTime, &realRect);

        SDL_SetRenderTarget(engine->renderer, NULL);
        SDL_RenderCopyEx(engine->renderer, _texture, &sdlRect, &sdlRect, computedRotation(), &sdlTransformOrigin,
                         SDL_RendererFlip::SDL_FLIP_NONE);

        Node::draw(gameTime);
    }

    void Drawable::destroy() {
        SDL_DestroyTexture(_texture);
        _texture = nullptr;

        Node::destroy();
    }

    void Drawable::paint(GameTime *gameTime, GRect *realRect) {

    }

}



