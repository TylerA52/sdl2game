#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include "render_window.h"
#include "entity.h"

class Tilemap {
    public:
        Tilemap(int mapWidth, int mapHeight, SDL_Texture* tileSet);
        void renderMap(RenderWindow& window);
    private:
        int mapWidth;
        int mapHeight;
        SDL_Texture* tileSet;
        std::vector<std::vector<int>> map;
};
