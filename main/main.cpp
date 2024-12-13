#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <vector>
#include "render_window.h"
#include "entity.h"
#include "tilemap.h"

int main(int argc, char* argv[]){
    int windowWidth = 1024;
    int windowHeight = 768;

    if (argc == 3) {
        windowWidth = std::atoi(argv[1]);
        windowHeight = std::atoi(argv[2]);
    }

    RenderWindow window("GAME", windowWidth, windowHeight);

    SDL_Texture* sprites = window.loadTexture("/home/tyler/Desktop/sdl2game/Images/characters.png");
    SDL_Texture* tiles = window.loadTexture("/home/tyler/Desktop/sdl2game/Images/basictiles.png");
    
    Tilemap tilemap(16, 12, tiles);

    Entity player(4, 0, 4, 7, sprites);
    
    // Entity entities[3] = {Entity(1, 0, 0, 0, tiles),
                          //Entity(1, 0, 25, 25, tiles),
                          //Entity(1, 0, 50, 50, tiles)};

    std::vector<Entity> entities =  {Entity(1, 0, 0, 0, tiles),
                                      Entity(1, 0, 25, 25, tiles),
                                      Entity(1, 0, 50, 50, tiles)};
    

    bool isRunning = true;

    SDL_Event event;
    
    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_w) {
                        //entity movement
                    }
                    break;
            }
        }

        window.clear();
     
        tilemap.renderMap(window);

        //for (Entity& i : entities){
          // window.render(i);
        //}

        window.render(player);
        window.display();

    }
    
    window.cleanUp();
    SDL_Quit();

    return 0;
}
