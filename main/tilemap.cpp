#include "tilemap.h"
#include "render_window.h"
#include <iostream>

Tilemap::Tilemap(int mapWidth, int mapHeight, SDL_Texture* tileSet)
    : mapWidth(mapWidth), mapHeight(mapHeight), tileSet(tileSet) {

    map.resize(mapHeight, std::vector<int>(mapWidth, 0));

    map = {
        {11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
        {11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
        {11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
        {11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
        {11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
        {11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
        {11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
        {11, 11, 11, 12, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
        {11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
        {11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
        {11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
        {11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
        {11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
        {11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
        {11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
        {11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11}
    };
}


void Tilemap::renderMap(RenderWindow& window) {
const int tilesPerRow = 8;

    for (int y = 0; y < mapHeight; y++){
        for (int x = 0; x < mapWidth; x++) {
            int tileIndex = map[y][x];

            if (tileIndex == 0) continue;

            int s_x = tileIndex % tilesPerRow;
            int s_y = tileIndex / tilesPerRow;

            Entity tileEntity(s_x, s_y, x, y, tileSet);
            window.render(tileEntity);
        }
    }
}
