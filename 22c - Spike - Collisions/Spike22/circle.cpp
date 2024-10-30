
#include <SDL.h>

#include "SDLcollision.h"
#include "circle.h"
#include "SDLcircle.h"



Circle::Circle() {
    //Initialize the offsets
    mPosX = 50;
    mPosY = 100;

    //Initialize the velocity
    mVelX = CIRCLE_VEL;
    mVelY = CIRCLE_VEL;
    
    //initalize centre circle (for colisions later)
    centX = mPosX + radius;
    centY = mPosY + radius;
}

void Circle::move()
{
    //Move the dot left or right
    mPosX += mVelX;

    //If the circle went too far to the left or right
    if ((mPosX < 0) || (mPosX + circleW > SCREEN_WIDTH))
    {
        //Move back
        mPosX -= mVelX;
        //flip velocity
        mVelX = -mVelX;
    }

    //Move the dot left or right
    mPosY += mVelY;

    //If the circle went too far up or down
    if ((mPosY < 0) || (mPosY + circleH > SCREEN_HEIGHT))
    {
        //Move back
        mPosY -= mVelY;
        //filp velocity
        mVelY = -mVelY;
    }

    //update centre
    centX = mPosX + radius;
    centY = mPosY + radius;
}

void Circle::render(SDL_Texture* texture, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { mPosX, mPosY, circleW, circleH };

    //Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //if colliding changes color
    if (colliding) {
        SDL_SetTextureColorMod(texture, 0, 255, 255);
    }
    else {
        SDL_SetTextureColorMod(texture, 255, 0, 0);
    }

    //Render to screen
    SDL_RenderCopyEx(cRenderer, texture, clip, &renderQuad, angle, center, flip);
}


void Circle::collisionCheck(Circle otherCircle) {
    colliding = circleCollision(*this, otherCircle);
}