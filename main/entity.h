#pragma once

class Entity {
    public:
        Entity(int s_x, int s_y, float p_x, float p_y, SDL_Texture* p_tex);
        float getX();
        float getY();
        int getWidth();
        int getHeight();
        void setX(float newX);
        void setY(float newY);
        SDL_Texture* getTex();
        SDL_Rect getCurrentFrame();
    private:
        float x, y;
        SDL_Rect currentFrame;
        SDL_Texture* tex;
};
