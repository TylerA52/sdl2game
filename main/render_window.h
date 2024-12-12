#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.h"


class RenderWindow {
    public:
        RenderWindow(const char* p_title, int p_w, int p_h);
        SDL_Texture* loadTexture(const char* p_filePath);
        void clear();
        void render(Entity& p_entity);
        void cleanUp();
        void display();
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
};
