//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <random>

#include "SDLgraphical.h"

//Screen dimension constants
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 800;

//window and background image
SDL_Surface* gBackground = NULL;
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;

void SDLgraphical()
{
    if (!init()) {
        printf("Failed to initialize!\n");
    }
    else {
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        }
        else {
            SDL_Event e;
            bool quit = false;
            SDL_BlitSurface(gBackground, NULL, gScreenSurface, NULL);
            SDL_UpdateWindowSurface(gWindow);
            while (quit == false) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                    else if (e.type == SDL_KEYDOWN) {
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_1://
                            break;
                        case SDLK_2://
                            break;
                        case SDLK_3://
                            break;
                        case SDLK_0://
                            break;
                        }
                    }
                }
            }
        }
    }
    close();//shutdown sdl
}
bool init() {
    //Loading success flag
    bool success = true;


    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    gBackground = SDL_LoadBMP("resourcesGraphical/Background.bmp");
    if (gBackground == NULL) {
        printf("Failed to load Background!\n");
        success = false;
    }

    return success;
}

void close() {
    //free background
    gBackground = NULL;

    //free image


    //Destroy window    
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_Quit();
}
