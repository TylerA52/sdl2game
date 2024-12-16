#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class textRenderer {
    public:
        textRenderer(SDL_Renderer* renderer, const std::string& fontPath, int fontSize);
        void renderText(const std::string& text, SDL_Color color, int x, int y);
    private:
        SDL_Renderer* renderer;
        TTF_Font* m_font;
};
