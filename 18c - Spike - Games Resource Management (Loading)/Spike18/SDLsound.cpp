/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <random>

#include "SDLsound.h"

//music track
Mix_Music* gMusic = NULL;

//sound effects
Mix_Chunk* gSound1 = NULL;
Mix_Chunk* gSound2 = NULL;
Mix_Chunk* gSound3 = NULL;

//window and background image
SDL_Surface* gImage = NULL;
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;


const int SCREEN_WIDTH = 275;
const int SCREEN_HEIGHT = 246;

void SDLsound() {
    if (!init()) {
        printf("Failed to initialize!\n");
    }
    else {
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        }else{
            SDL_Event e;
            bool quit = false;
            SDL_BlitSurface(gImage, NULL, gScreenSurface, NULL);
            SDL_UpdateWindowSurface(gWindow);
            while (quit == false) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                    else if (e.type == SDL_KEYDOWN) {
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_1://play first sound
                            Mix_PlayChannel(-1, gSound1, 0);
                            break;
                        case SDLK_2://play second sound
                            Mix_PlayChannel(-1, gSound2, 0);
                            break;
                        case SDLK_3://play third sound
                            Mix_PlayChannel(-1, gSound3, 0);
                            break;
                        case SDLK_0://music
                            //If music isnt playing
                            if (Mix_PlayingMusic() == 0)
                            {
                                //Play the music
                                Mix_PlayMusic(gMusic, -1);
                            }
                            //If music playing
                            else
                            {
                                //If music is paused
                                if (Mix_PausedMusic() == 1)
                                {
                                    //Resume the music
                                    Mix_ResumeMusic();
                                }
                                //If music is playing
                                else
                                {
                                    //Pause the music
                                    Mix_PauseMusic();
                                }
                            }
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
        //Initialize SDL_mixer
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
            success = false;
        }
    }
    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    gImage = SDL_LoadBMP("resourcesSound/Background.bmp");
    if (gImage == NULL) {
        printf("Failed to load Background!\n");
        success = false;
    }
    //Load music
    gMusic = Mix_LoadMUS("resourcesSound/GuitarLoop.wav");
    if (gMusic == NULL)
    {
        printf("Failed to load guitar music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    //Load sound effects
    gSound1 = Mix_LoadWAV("resourcesSound/PianoChord.wav");
    if (gSound1 == NULL)
    {
        printf("Failed to load first sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    gSound2 = Mix_LoadWAV("resourcesSound/SharpieSound.wav");
    if (gSound2 == NULL)
    {
        printf("Failed to load second sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    gSound3 = Mix_LoadWAV("resourcesSound/Whoosh.wav");
    if (gSound3 == NULL)
    {
        printf("Failed to load third sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    return success;
}

void close() {
    //free background
    gImage = NULL;

    //Free the sound effects
    Mix_FreeChunk(gSound1);
    Mix_FreeChunk(gSound2);
    Mix_FreeChunk(gSound3);
    gSound1 = NULL;
    gSound2 = NULL;
    gSound3 = NULL;

    //Free the music
    Mix_FreeMusic(gMusic);
    gMusic = NULL;

    //Destroy window    
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    Mix_Quit();
    SDL_Quit();
}