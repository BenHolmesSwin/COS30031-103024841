#pragma once


class Square {
public:
    //The dimensions of the square
    int squareW = 20;
    int squareH = 20;

    //The X and Y offsets of the square
    int mPosX, mPosY;

    //Maximum axis velocity of the square
    static const int SQUARE_VEL = 1;

    //Initializes the variables
    Square();

    //Moves the dot
    void move();

    //Shows the dot on the screen
    void render();

    //checking collision
    void collisionCheck(Square otherSquare);

private:

    //the collision boolean
    bool colliding = false;

    //The velocity of the square
    int mVelX, mVelY;
};