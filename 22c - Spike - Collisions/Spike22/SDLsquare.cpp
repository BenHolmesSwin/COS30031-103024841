
#include <SDL.h>
#include <stdio.h>
#include <random>
#include <string>
#include <sstream>
#include <SDL_image.h>
#include <SDL_timer.h>

#include "square.h"
#include "SDLsquare.h"
#include "MyTimer.h"

//Screen dimension constants
const int SQUARE_SCREEN_WIDTH = 400;
const int SQUARE_SCREEN_HEIGHT = 400;
const int SCREEN_TICKS_PER_FRAME = 10;

//window and background image
SDL_Window* sWindow = NULL;
SDL_Surface* sScreenSurface = NULL;

//renderer
SDL_Renderer* sRenderer = NULL;


//moving square
Square movSquare;

//stationary square
Square stSquare;

void SDLsquare()
{
    if (!squareInit()) {
        printf("Failed to initialize!\n");
    }
    else {
        if (!squareLoadMedia()) {
            printf("Failed to load media!\n");
        }
        else {
            //event handler
            SDL_Event e;
            //loop flag
            bool quit = false;

            //The frames per second cap timer
            MyTimer capTimer;

            while (quit == false) {
                //Start cap timer
                capTimer.start();
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }

                //Move the dot
                movSquare.move();

                //Clear screen
                SDL_SetRenderDrawColor(sRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(sRenderer);

                //checking moving is colliding with stationary
                movSquare.collisionCheck(stSquare);
                
                //rendering squares
                stSquare.render();
                movSquare.render();

                //Update screen
                SDL_RenderPresent(sRenderer);

                //If frame finished early
                int frameTicks = capTimer.getTicks();
                if (frameTicks < SCREEN_TICKS_PER_FRAME)
                {
                    //Wait remaining time
                    SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
                }
            }
        }
    }
    squareClose();//shutdown sdl
}

bool squareInit() {
    //Loading success flag
    bool success = true;


    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window
        sWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SQUARE_SCREEN_WIDTH, SQUARE_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        sRenderer = SDL_CreateRenderer(sWindow, -1, SDL_RENDERER_ACCELERATED);
        if (sWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Get window surface
            sScreenSurface = SDL_GetWindowSurface(sWindow);
        }
    }
    return success;
}

bool squareLoadMedia()
{
    //Loading success flag
    bool success = true;

    //nothing to load

    return success;
}

void squareClose() {

    //Destroy window
    SDL_DestroyRenderer(sRenderer);
    SDL_DestroyWindow(sWindow);
    sWindow = NULL;
    SDL_Quit();
}