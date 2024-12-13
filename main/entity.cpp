#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.h"

Entity::Entity(int s_x, int s_y, float p_x, float p_y, SDL_Texture* p_tex)
    :x(p_x), y(p_y), tex(p_tex)
{
    currentFrame.x = s_x * 16;
    currentFrame.y = s_y * 16;
    currentFrame.w = 16; // dimensions of source
    currentFrame.h = 16;
}

float Entity::getX(){
    return x;
}

float Entity::getY(){
    return y;
}

void Entity::setX(float newX){
    x = newX;
}
void Entity::setY(float newY){
    y = newY;
}

SDL_Texture* Entity::getTex(){
    return tex;
}

SDL_Rect Entity::getCurrentFrame(){
    return currentFrame;
}


