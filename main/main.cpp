#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstdlib>
#include <vector>
#include "render_window.h"
#include "entity.h"
#include "tilemap.h"
#include "text.h"

bool IsMouseOverButton(int mouseX, int mouseY, textRenderer& text);
bool checkCollision(Entity& entity1, std::vector<Entity>& entities);

int main(int argc, char* argv[]){
    int windowWidth = 1024;
    int windowHeight = 768;

    if (argc == 3) {
        windowWidth = std::atoi(argv[1]);
        windowHeight = std::atoi(argv[2]);
    }
    
    if (TTF_Init() == -1) {
        std::cerr << "SDL ttf could not initialize, error: " << TTF_GetError();
        SDL_Quit();
        return 1;
    }

    RenderWindow window("GAME", windowWidth, windowHeight);

    SDL_Renderer* renderer = window.getRenderer();

    SDL_Texture* sprites = window.loadTexture("/home/tyler/Desktop/sdl2game/Images/characters.png");
    SDL_Texture* tiles = window.loadTexture("/home/tyler/Desktop/sdl2game/Images/basictiles.png");
    
    textRenderer titleFont(renderer, "/home/tyler/Desktop/sdl2game/Images/ARCADECLASSIC.TTF", 100);
    textRenderer regFont(renderer, "/home/tyler/Desktop/sdl2game/Images/ARCADECLASSIC.TTF", 36);
    SDL_Color color = {255, 255, 255};

    Tilemap tilemap(16, 12, tiles);

    Entity player(4, 0, 4, 7, sprites);

    
    std::vector<Entity> objects = {Entity(3, 8, 5, 6, tiles),
                                   Entity(7, 3, 12, 3, tiles)};

    std::vector<Entity> npcmodels =  {Entity(10, 0, 8, 2, sprites),
                                      Entity(0, 4, 9, 8, sprites),
                                      Entity(5, 5, 10, 8, sprites)};
    
    bool map1 = true;
    bool pause = false;
    bool isRunning = true;

    SDL_Event event;
    
    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;
                case SDL_KEYDOWN:
                    // Movement
                    if (event.key.keysym.sym == SDLK_UP) {
                        player = Entity (3, 3, player.getX(), player.getY(), sprites);
                        player.setY(player.getY() - 1);

                        if (checkCollision(player, npcmodels)|| checkCollision(player, objects)){ // only works on my arrays, what about map tiles?
                            player.setY(player.getY() + 1);
                        }
                    }
                    if (event.key.keysym.sym == SDLK_LEFT) {
                        player = Entity (5, 1, player.getX(), player.getY(), sprites);
                        player.setX(player.getX() - 1);

                        if (checkCollision(player, npcmodels) || checkCollision(player, objects)){
                            player.setX(player.getX() + 1);
                        }
                    }
                    if (event.key.keysym.sym == SDLK_DOWN) {
                        player = Entity (4, 0, player.getX(), player.getY(), sprites);
                        player.setY(player.getY() + 1);

                        if (checkCollision(player, npcmodels) || checkCollision(player, objects)){
                            player.setY(player.getY() - 1);
                        }
                    }
                    if (event.key.keysym.sym == SDLK_RIGHT) {
                        player = Entity (5, 2, player.getX(), player.getY(), sprites);
                        player.setX(player.getX() + 1);

                        if (checkCollision(player, npcmodels) || checkCollision(player, objects)){
                            player.setX(player.getX() - 1);
                        }
                    }
                    
                    // Turning on and off pause screen bool
                    if (event.key.keysym.sym == SDLK_ESCAPE){
                        if (pause){
                            pause = false;
                        }
                        else {
                            pause = true;
                        }
                    }

                    // Testing a location to go to a new map
                    if (player.getX() == 0 && player.getY() == 9){
                        std::cout << "arrived\n";
                    }
               case SDL_MOUSEBUTTONDOWN:

                    if (event.type == SDL_MOUSEBUTTONDOWN){
                        int mouseX, mouseY;
                        SDL_GetMouseState(&mouseX, &mouseY);
                        if (IsMouseOverButton(mouseX, mouseY, titleFont)){
                            std::cout << "Button clicked\n";
                        }
                    }

                    break; 
            }
        }

        window.clear();

        if (map1){
            tilemap.renderMap(window);
        }

        for (Entity& i : npcmodels){
           window.render(i);
        }

        for (Entity& i : objects){
            window.render(i);
        }

        window.render(player);

        // Pause screen
        if (pause){
            titleFont.renderText("Pause", color, 365, 325);
        }

        window.display();

    }
    
    window.cleanUp();
    SDL_Quit();

    return 0;
}


// TO DO: Put these in header/implementation files

bool checkCollision(Entity& entity1, std::vector<Entity>& entities){
    
    int x1 = entity1.getX() * 4 * 16;
    int y1 = entity1.getY() * 4 * 16;
    int width1 = entity1.getWidth() * 4;
    int height1 = entity1.getHeight() * 4;

    for (Entity& entity2 : entities) {
        int x2 = entity2.getX() * 4 * 16;
        int y2 = entity2.getY() * 4 * 16;
        int width2 = entity2.getWidth() * 4;
        int height2 = entity2.getHeight()  * 4;

        if (x1 + width1 <= x2 || x1 >= x2 + width2 ||
            y1 + height1 <= y2 || y1 >= y2 + height2) {

            continue;
        }
        else {
            return true;
        }
    }
    return false;
}

// Check text.cpp for ways of getting the x y w h from the textRect (hiddent within class currently)

bool IsMouseOverButton(int mouseX, int mouseY, textRenderer& text){
    return mouseX >= text.getX() && mouseX <= text.getX() + text.getW() &&
           mouseY >= text.getY() && mouseY <= text.getY() + text.getH();
}
