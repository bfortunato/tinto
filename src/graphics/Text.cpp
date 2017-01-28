//
// Created by Bruno Fortunato on 31/05/16.
//

#include <SDL.h>
#include <sstream>
#include <cmath>

#include "tinto/graphics/Text.h"
#include "tinto/utils/Thread.h"

namespace tinto {

    class _LineTexture {
    public:
        GSize size;
        SDL_Texture *texture;
    };

    Text::Text(GameEngine *engine) : Node(engine) {

    }

    Text::~Text() {

    }


    void Text::loadFont(std::string path, int size) {
        _font = TTF_OpenFont(path.c_str(), size);

        if (_font == nullptr) {
            SDL_Log("Error loading font: %s (%s)", path.c_str(), SDL_GetError());
            throw std::exception();
        }
    }

    void Text::invalidate() {
        Thread::checkMainThread();

        std::vector<std::string> lines;
        std::stringstream ss(text);
        std::string item;
        while (std::getline(ss, item, '\n')) {
            lines.push_back(item);
        }

        auto lineTextures = std::vector<_LineTexture *>();
        auto shadowLineTextures = std::vector<_LineTexture *>();

        if (_texture != nullptr) {
            SDL_DestroyTexture(_texture);
            _texture = nullptr;
        }

        float maxWidth = 0;
        float height = 0;
        for (auto line : lines) {
            if (line == "") {
                line = " ";
            }

            auto surface = TTF_RenderText_Blended(_font, line.c_str(), textColor.toSDL());
            auto texture = SDL_CreateTextureFromSurface(engine->renderer, surface);
            auto ln = new _LineTexture();
            ln->size = engine->metrics->toLogical(GSize(surface->w, surface->h));
            ln->texture = texture;
            lineTextures.push_back(ln);
            SDL_FreeSurface(surface);

            if (dropShadow) {
                auto ssurface = TTF_RenderText_Blended(_font, line.c_str(), {0, 0, 0});
                auto stexture = SDL_CreateTextureFromSurface(engine->renderer, ssurface);
                auto sln = new _LineTexture();
                sln->size = engine->metrics->toLogical(GSize(ssurface->w, ssurface->h));
                sln->texture = stexture;
                shadowLineTextures.push_back(sln);
                SDL_FreeSurface(ssurface);
            }

            maxWidth = std::max(ln->size.width, maxWidth);
            height += ln->size.height;
        }

        rect.width = maxWidth;
        rect.height = height;

        _size = engine->metrics->toReal(GSize(maxWidth, height));

        GRect realRect = engine->metrics->toReal(rect);

        _texture = SDL_CreateTexture(engine->renderer,
                                     SDL_PIXELFORMAT_RGBA8888,
                                     SDL_TEXTUREACCESS_TARGET,
                                     static_cast<Uint32>(realRect.width),
                                     static_cast<Uint32>(realRect.height)
        );

        SDL_SetRenderTarget(engine->renderer, _texture);
        SDL_SetTextureBlendMode(_texture, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, 0);
        SDL_RenderClear(engine->renderer);
        float x = 0;
        float y = 0;
        float realWidth = _size.width;
        for (auto single : lineTextures) {
            GSize lineSize = engine->metrics->toReal(single->size);

            SDL_Rect srcRect = {0, 0, (int) lineSize.width, (int) lineSize.height};
            x = realWidth / 2 - lineSize.width / 2;
            SDL_Rect dstRect = {(int) x, (int) y, (int) lineSize.width, (int) lineSize.height};
            y += lineSize.height;
            SDL_RenderCopy(engine->renderer, single->texture, &srcRect, &dstRect);
            SDL_DestroyTexture(single->texture);

            delete single;
        }

        if (dropShadow) {
            _shadowTexture = SDL_CreateTexture(engine->renderer,
                                               SDL_PIXELFORMAT_RGBA8888,
                                               SDL_TEXTUREACCESS_TARGET,
                                               static_cast<Uint32>(realRect.width),
                                               static_cast<Uint32>(realRect.height)
            );

            SDL_SetRenderTarget(engine->renderer, _shadowTexture);
            SDL_SetTextureBlendMode(_shadowTexture, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, 0);
            SDL_RenderClear(engine->renderer);
            float x = 0;
            float y = 0;
            float realWidth = _size.width;
            for (auto single : shadowLineTextures) {
                GSize lineSize = engine->metrics->toReal(single->size);

                SDL_Rect srcRect = {0, 0, (int) lineSize.width, (int) lineSize.height};
                x = realWidth / 2 - lineSize.width / 2;
                SDL_Rect dstRect = {(int) x, (int) y, (int) lineSize.width, (int) lineSize.height};
                y += lineSize.height;
                SDL_RenderCopy(engine->renderer, single->texture, &srcRect, &dstRect);
                SDL_DestroyTexture(single->texture);

                delete single;
            }
        }

        SDL_SetRenderTarget(engine->renderer, NULL);
    }

    void Text::draw(GameTime *gameTime) {
        if (!active) {
            return;
        }

        if (_font == nullptr) {
            return;
        }

        if (_texture == nullptr) {
            return;
        }

        SDL_SetRenderDrawBlendMode(engine->renderer, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(_texture, static_cast<Uint8>(this->alpha * 255.0f));

        GRect realRect = this->computedRealRect();
        GPoint transformOrigin(realRect.width * 0.5f, realRect.height * 0.5f);

        SDL_Rect sdlRect = realRect.toSDL();
        SDL_Point sdlTransformOrigin = transformOrigin.toSDL();

        SDL_Rect srcSdlRect = {0, 0, static_cast<int>(_size.width), static_cast<int>(_size.height)};

        SDL_RendererFlip sdlFlip = SDL_RendererFlip::SDL_FLIP_NONE;
        switch (flip) {
            case Flip::NONE:
                sdlFlip = SDL_RendererFlip::SDL_FLIP_NONE;
                break;
            case Flip::HORIZONTAL:
                sdlFlip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
                break;
            case Flip::VERTICAL:
                sdlFlip = SDL_RendererFlip::SDL_FLIP_VERTICAL;
                break;
        }

        if (dropShadow) {
            float distance = 2;
            SDL_Rect shadowRect = {sdlRect.x - static_cast<int>(distance), sdlRect.y + static_cast<int>(distance),
                                   sdlRect.w, sdlRect.h};
            SDL_SetTextureAlphaMod(_shadowTexture, static_cast<Uint8>(this->alpha * 100.0f));
            SDL_RenderCopyEx(engine->renderer, _shadowTexture, &srcSdlRect, &shadowRect, computedRotation(),
                             &sdlTransformOrigin, sdlFlip);
        }

        SDL_RenderCopyEx(engine->renderer, _texture, &srcSdlRect, &sdlRect, computedRotation(), &sdlTransformOrigin,
                         sdlFlip);

        Node::draw(gameTime);
    }


    void Text::destroy() {
        Node::destroy();

        if (_texture != nullptr) {
            SDL_DestroyTexture(_texture);
            _texture = nullptr;
        }

        if (_shadowTexture == nullptr) {
            SDL_DestroyTexture(_shadowTexture);
            _shadowTexture = nullptr;
        }

        TTF_CloseFont(_font);
        _font = nullptr;
    }

}