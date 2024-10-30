#pragma once



class Circle
{
public:
    //The dimensions of the dot
    int circleW = 20;
    int circleH = 20;

    int radius = circleH / 2;

    //Maximum axis velocity of the dot
    static const int CIRCLE_VEL = 1;

    //Initializes the variables
    Circle();

    //Moves the dot
    void move();

    //Shows the dot on the screen
    void render(SDL_Texture* texture, bool collision, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
    //The X and Y offsets of the dot
    int mPosX, mPosY;

    //The velocity of the dot
    int mVelX, mVelY;

    int centX, centY;
};