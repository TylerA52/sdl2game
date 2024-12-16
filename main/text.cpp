#include "text.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>

textRenderer::textRenderer(SDL_Renderer* renderer, const std::string& fontPath, int fontSize)
    : renderer(renderer), m_font(nullptr) {

    m_font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!m_font){
        std::cout << "failed to load font: " << TTF_GetError();
        return;
    }
}

void textRenderer::renderText(const std::string& text, SDL_Color color, int x, int y) {
    
    SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, text.c_str(), color);
    if (!textSurface){
        std::cout << "failed to create surface: " << TTF_GetError();
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!texture){
        std::cout << "failed to create texture from surface: " << SDL_GetError();
        SDL_FreeSurface(textSurface);
        return;
    }

    int textWidth = textSurface->w;
    int textHeight = textSurface->h;

    SDL_FreeSurface(textSurface);

    SDL_Rect renderQuad = {x, y, textWidth, textHeight};
    SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);
    SDL_DestroyTexture(texture);
}
