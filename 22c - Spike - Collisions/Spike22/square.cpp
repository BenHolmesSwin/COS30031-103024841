
#include "SDLsquare.h"
#include "square.h"
#include "SDLcollision.h"

Square::Square() {
    //Initialize the offsets
    mPosX = 50;
    mPosY = 100;

    //Initialize the velocity
    mVelX = SQUARE_VEL;
    mVelY = SQUARE_VEL;
}

void Square::move()
{
    //Move the dot left or right
    mPosX += mVelX;

    //If the square went too far to the left or right
    if ((mPosX < 0) || (mPosX + squareW > SQUARE_SCREEN_WIDTH))
    {
        //Move back
        mPosX -= mVelX;
        //flip velocity
        mVelX = -mVelX;
    }

    //Move the dot left or right
    mPosY += mVelY;

    //If the square went too far up or down
    if ((mPosY < 0) || (mPosY + squareH > SQUARE_SCREEN_HEIGHT))
    {
        //Move back
        mPosY -= mVelY;
        //filp velocity
        mVelY = -mVelY;
    }
}

void Square::render() {
    //Render red filled quad
    SDL_Rect fillRect = { mPosX, mPosY,squareW,squareH};
    if (colliding) {
        SDL_SetRenderDrawColor(sRenderer, 0x00, 0xFF, 0x00, 0xFF);
    }
    else {
        SDL_SetRenderDrawColor(sRenderer, 0xFF, 0x00, 0x00, 0xFF);
    }
    SDL_RenderFillRect(sRenderer, &fillRect);
}

void Square::collisionCheck(Square otherSquare) {
    colliding = squareCollision(*this, otherSquare);
}