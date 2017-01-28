//
//  Sprite.cpp
//  WheelOfFortune
//
//  Created by Bruno Fortunato on 20/05/16.
//  Copyright © 2016 Bruno Fortunato. All rights reserved.
//

#include <sstream>

#include "tinto/graphics/Sprite.h"
#include "tinto/utils/Thread.h"

namespace tinto {

    Sprite::Sprite(GameEngine *engine) : Node(engine) {

    }

    void Sprite::load(std::string path) {
        _loadComplete = false;
        name = "";

        _surface = IMG_Load(path.c_str());

        if (_surface == nullptr) {
            SDL_Log("Cannot load image: %s (%s)", path.c_str(), SDL_GetError());
            throw std::exception();
        }

        name = path;

        realSize = GSize(_surface->w, _surface->h);
        GRect realRect(0, 0, _surface->w, _surface->h);

        rect = engine->metrics->toLogical(realRect);
        srcRect = GRect(0, 0, 1, 1);

        completeLoad();
    }

    void Sprite::completeLoad() {
        Thread::checkMainThread();

        if (_texture != nullptr) {
            SDL_DestroyTexture(_texture);
            _texture = nullptr;
        }

        _texture = SDL_CreateTextureFromSurface(engine->renderer, _surface);

        SDL_FreeSurface(_surface);
        _surface = nullptr;

        if (_texture == nullptr) {
            SDL_Log("Cannot create texture from surface for image %s: %s", name.c_str(), SDL_GetError());
            throw std::exception();
        }

        _loadComplete = true;
    }

    void Sprite::loadScaled(std::string path, std::string ext) {
        std::stringstream scaledPath;
        scaledPath << path << "@" << engine->metrics->density << "x." << ext;
        load(scaledPath.str());
    }

    void Sprite::update(GameTime *gameTime) {
        if (!_loadComplete) {
            completeLoad();
        }

        Node::update(gameTime);
    }

    void Sprite::draw(GameTime *gameTime) {
        if (!active) {
            return;
        }

        if (_texture == nullptr) {
            Node::draw(gameTime);
            return;
        }

        SDL_SetRenderDrawBlendMode(engine->renderer, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(_texture, static_cast<Uint8>(this->computedAlpha() * 255.0f));

        GRect realRect = this->computedRealRect();
        GPoint transformOrigin(realRect.width * 0.5f, realRect.height * 0.5f);

        SDL_Rect sdlRect = realRect.toSDL();
        SDL_Point sdlTransformOrigin = transformOrigin.toSDL();

        SDL_Rect srcSdlRect = {
                static_cast<int>(realSize.width * srcRect.x),
                static_cast<int>(realSize.height * srcRect.y),
                static_cast<int>(realSize.width * srcRect.width),
                static_cast<int>(realSize.height * srcRect.height)
        };

        bool scaleFlipX = computedScaleX() < 0;
        bool scaleFlipY = computedScaleY() < 0;


        SDL_RendererFlip sdlFlip = SDL_RendererFlip::SDL_FLIP_NONE;

        if ((flip & Flip::NONE) == Flip::NONE) {
            if (scaleFlipY) {
                sdlFlip = static_cast<SDL_RendererFlip>(sdlFlip | SDL_RendererFlip::SDL_FLIP_VERTICAL);
            }

            if (scaleFlipX) {
                sdlFlip = static_cast<SDL_RendererFlip>(sdlFlip | SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
            }
        }

        if ((flip & Flip::HORIZONTAL) == Flip::HORIZONTAL) {
            if (!scaleFlipY) {
                sdlFlip = static_cast<SDL_RendererFlip>(sdlFlip | SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
            }
        }

        if ((flip & Flip::VERTICAL) == Flip::VERTICAL) {
            if (!scaleFlipY) {
                sdlFlip = static_cast<SDL_RendererFlip>(sdlFlip | SDL_RendererFlip::SDL_FLIP_VERTICAL);
            }
        }

        SDL_RenderCopyEx(engine->renderer, _texture, &srcSdlRect, &sdlRect, computedRotation(), &sdlTransformOrigin,
                         sdlFlip);

        Node::draw(gameTime);
    }

    void Sprite::destroy() {
        if (_texture != nullptr) {
            SDL_DestroyTexture(_texture);
            _texture = nullptr;
        }

        if (_surface != nullptr) {
            SDL_FreeSurface(_surface);
            _surface = nullptr;
        }

        Node::destroy();
    }

}

