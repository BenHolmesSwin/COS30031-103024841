#pragma once

#include <SDL.h>

class Circle
{
public:
    //The dimensions of the circle
    int circleW = 20;
    int circleH = 20;

    int radius = circleH / 2;

    //Maximum axis velocity of the circle
    static const int CIRCLE_VEL = 1;

    //Initializes the variables
    Circle();

    //Moves the circle
    void move();

    //centre point coords, for collison detection
    int centX, centY;

    //Shows the circle on the screen (uses texture cause no easy circle creation)
    void render(SDL_Texture* texture, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    //checking collision
    void collisionCheck(Circle otherCircle);

private:
    //The X and Y offsets of the circle (the top left corner)
    int mPosX, mPosY;

    //The velocity of the cirlce
    int mVelX, mVelY;

    bool colliding = false;

};