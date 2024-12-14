#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <vector>
#include "render_window.h"
#include "entity.h"
#include "tilemap.h"


bool checkCollision(Entity& entity1, Entity& entity2);


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
    Entity testNPC(5, 5, 11, 11, sprites); //testing collision against this npc
    
    std::vector<Entity> objects = {Entity(3, 8, 5, 6, tiles),
                                   Entity(7, 3, 12, 3, tiles)};

    std::vector<Entity> npcmodels =  {Entity(10, 0, 8, 2, sprites),
                                      Entity(0, 4, 9, 8, sprites),
                                      Entity(5, 5, 10, 8, sprites)};
    

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
                    
                    if (checkCollision(player, testNPC)) {
                        std::cout << "Collision detected!\n";
                    }
                    else{
                        std::cout << "No collision\n";
                    }

                    break;
                    
            }
        }

        window.clear();
     
        tilemap.renderMap(window);

        for (Entity& i : npcmodels){
           window.render(i);
        }

        for (Entity& i : objects){
            window.render(i);
        }
        window.render(testNPC);
        window.render(player);
        window.display();

    }
    
    window.cleanUp();
    SDL_Quit();

    return 0;
}



bool checkCollision(Entity& entity1, Entity& entity2){
    
    int x1 = entity1.getX();
    int y1 = entity1.getY();
    int width1 = entity1.getWidth();
    int height1 = entity1.getHeight();

    int x2 = entity2.getX();
    int y2 = entity2.getY();
    int width2 = entity2.getWidth();
    int height2 = entity2.getHeight();

    if (x1 + width1 <= x2 || x1 >= x2 + width2 ||
        y1 + height1 <= y2 || y1 >= y2 + height2) {
        return false;
    }
    return true;
}
    
