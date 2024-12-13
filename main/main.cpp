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
    

    std::vector<Entity> npcmodels =  {Entity(10, 0, 8, 2, sprites),
                                      Entity(0, 4, 8, 8, sprites),
                                      Entity(5, 5, 9, 8, sprites)};
    

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
                        player = Entity (3, 3, player.getX(), player.getY(), sprites);
                        player.setY(player.getY() - 1);
                    }
                    if (event.key.keysym.sym == SDLK_a) {
                        player = Entity (5, 1, player.getX(), player.getY(), sprites);
                        player.setX(player.getX() - 1);
                                }
                    if (event.key.keysym.sym == SDLK_s) {
                        player = Entity (4, 0, player.getX(), player.getY(), sprites);
                        player.setY(player.getY() + 1);
                                }
                    if (event.key.keysym.sym == SDLK_d) {
                        player = Entity (5, 2, player.getX(), player.getY(), sprites);
                        player.setX(player.getX() + 1);
                                }                       
                    break;
            }
        }

        window.clear();
     
        tilemap.renderMap(window);

        for (Entity& i : npcmodels){
           window.render(i);
        }

        window.render(player);
        window.display();

    }
    
    window.cleanUp();
    SDL_Quit();

    return 0;
}
