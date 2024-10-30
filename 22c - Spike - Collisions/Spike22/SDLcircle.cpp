

#include <SDL.h>
#include <stdio.h>
#include <random>
#include <string>
#include <sstream>
#include <SDL_image.h>
#include <SDL_timer.h>

#include "circle.h"
#include "SDLcircle.h"
#include "MyTimer.h"

//Screen dimension constants
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;
const int SCREEN_TICKS_PER_FRAME = 10;

//window and background image
SDL_Window* cWindow = NULL;
SDL_Surface* cScreenSurface = NULL;

//renderer
SDL_Renderer* cRenderer = NULL;


//moving circle
Circle movCircle;
SDL_Texture* movCircleTexture;

//stationary circle
Circle stCircle;
SDL_Texture* stCircleTexture;

void SDLcircle()
{
    if (!circleInit()) {
        printf("Failed to initialize!\n");
    }
    else {
        if (!circleLoadMedia()) {
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
                movCircle.move();

                //Clear screen
                SDL_SetRenderDrawColor(cRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(cRenderer);

                //checking moving is colliding with stationary
                movCircle.collisionCheck(stCircle);

                //Render objects
                stCircle.render(stCircleTexture);
                movCircle.render(movCircleTexture);

                //Update screen
                SDL_RenderPresent(cRenderer);

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
    circleClose();//shutdown sdl
}

bool circleInit() {
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
        cWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        cRenderer = SDL_CreateRenderer(cWindow, -1, SDL_RENDERER_ACCELERATED);
        if (cWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Get window surface
            cScreenSurface = SDL_GetWindowSurface(cWindow);
        }
    }
    return success;
}

bool circleLoadMedia()
{
    //Loading success flag
    bool success = true;

    SDL_Texture* newTexture = NULL;

    //moving circle texture
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load("circleTexture/circle.bmp");
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", "circleTexture/circle.bmp", IMG_GetError());
    }
    else
    {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));

        //Create moving circle texture from surface pixels
        movCircleTexture = SDL_CreateTextureFromSurface(cRenderer, loadedSurface);
        if (movCircleTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", "circleTexture/circle.bmp", SDL_GetError());
        }
        else
        {
            //Get image dimensions
            movCircle.circleW = loadedSurface->w;
            movCircle.circleH = loadedSurface->h;
        }


        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    //stationary circle texture
    //Load image at specified path
    loadedSurface = IMG_Load("circleTexture/circle.bmp");
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", "circleTexture/circle.bmp", IMG_GetError());
    }
    else
    {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));

        //Create moving circle texture from surface pixels
        stCircleTexture = SDL_CreateTextureFromSurface(cRenderer, loadedSurface);
        if (movCircleTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", "circleTexture/circle.bmp", SDL_GetError());
        }
        else
        {
            //Get image dimensions
            stCircle.circleW = loadedSurface->w;
            stCircle.circleH = loadedSurface->h;
        }


        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return success;
}

void circleClose() {

    //Destroy window
    SDL_DestroyRenderer(cRenderer);
    SDL_DestroyWindow(cWindow);
    cWindow = NULL;
    SDL_Quit();
}





