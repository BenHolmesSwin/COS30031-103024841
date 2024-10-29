//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <random>

#include "SDLgraphical.h"

//Screen dimension constants
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 800;

//window and background image
bool backgroundRend = true;
SDL_Surface* gBackground = NULL;
SDL_Texture* gBackgroundTexture;
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;

//renderer
SDL_Renderer* gRenderer = NULL;

//Scene sprites
SDL_Rect gSpriteClips[3];
SDL_Texture* gSpriteSheetTexture;
int textHeight = 0;
int textWidth = 0;

//sprite1 render values
bool sprite1Rend = true;
int sprite1Rendx = 0;
int sprite1Rendy = 0;
//sprite1 render values
bool sprite2Rend = true;
int sprite2Rendx;
int sprite2Rendy;
//sprite3 render values
bool sprite3Rend = true;
int sprite3Rendx;
int sprite3Rendy;

void SDLgraphical()
{
    if (!graphInit()) {
        printf("Failed to initialize!\n");
    }
    else {
        if (!graphLoadMedia()) {
            printf("Failed to load media!\n");
        }
        else {
            SDL_Event e;
            bool quit = false;
            SDL_UpdateWindowSurface(gWindow);
            while (quit == false) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                    else if (e.type == SDL_KEYDOWN) {
                        
                        std::string toggle = "OFF";
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_1://tile 1 toggle
                            sprite1Rend = !sprite1Rend;
                            break;
                        case SDLK_2://tile 2 toggle
                            sprite2Rend = !sprite2Rend;
                            break;
                        case SDLK_3://tile 3 toggle
                            sprite3Rend = !sprite3Rend;
                            break;
                        case SDLK_0://background toggle
                            backgroundRend = !backgroundRend;
                            break;
                        }
                        
                    }
                    SDL_RenderClear(gRenderer);
                    if (backgroundRend) {
                        SDL_RenderCopy(gRenderer,gBackgroundTexture,NULL,NULL);
                    }
                    if (sprite1Rend) {
                        renderSprite(sprite1Rendx, sprite1Rendy, &gSpriteClips[0]);
                    }
                    if (sprite2Rend) {
                        renderSprite(sprite2Rendx, sprite2Rendy, &gSpriteClips[1]);
                    }
                    if (sprite3Rend) {
                        renderSprite(sprite3Rendx, sprite3Rendy, &gSpriteClips[2]);
                    }
                    SDL_RenderPresent(gRenderer);
                }
            }
        }
    }
    graphClose();//shutdown sdl
}
bool graphInit() {
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
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
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

bool graphLoadMedia()
{
    //Loading success flag
    bool success = true;

    gBackground = SDL_LoadBMP("resourcesGraphical/Background.bmp");
    gBackgroundTexture = SDL_CreateTextureFromSurface(gRenderer, gBackground);
    if (gBackground == NULL) {
        printf("Failed to load Background!\n");
        success = false;
    }
    SDL_Surface* loadedSurface = SDL_LoadBMP("resourcesGraphical/sprites.bmp");
    gSpriteSheetTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if (gSpriteSheetTexture == NULL) {
        printf("Unable to create texture from %s! SDL Error: %s\n", "resourcesGraphical/sprites.bmp", SDL_GetError());
        success = false;
    }
    else {
        textHeight = loadedSurface->h;
        textWidth = loadedSurface->w;

        // initialize random seed:
        srand(time(NULL));

        //Set leftmost sprite (circle)
        gSpriteClips[0].x = 0;
        gSpriteClips[0].y = 0;
        gSpriteClips[0].w = 70;
        gSpriteClips[0].h = 75;
        sprite1Rendx = rand() % (SCREEN_WIDTH - gSpriteClips[0].w);
        sprite1Rendy = rand() % (SCREEN_HEIGHT - gSpriteClips[0].h);


        //Set middle sprite (triangle)
        gSpriteClips[1].x = 70;
        gSpriteClips[1].y = 0;
        gSpriteClips[1].w = 60;
        gSpriteClips[1].h = 75;
        sprite2Rendx = rand() % (SCREEN_WIDTH - gSpriteClips[1].w);
        sprite2Rendy = rand() % (SCREEN_HEIGHT - gSpriteClips[1].h);

        //Set rightmost sprite (square)
        gSpriteClips[2].x = 131;
        gSpriteClips[2].y = 6;
        gSpriteClips[2].w = 55;
        gSpriteClips[2].h = 56;
        sprite3Rendx = rand() % (SCREEN_WIDTH - gSpriteClips[2].w);
        sprite3Rendy = rand() % (SCREEN_HEIGHT - gSpriteClips[2].h);
    }

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);

    return success;
}

void graphClose() {
    //free background
    gBackground = NULL;

    //free image
    SDL_DestroyTexture(gSpriteSheetTexture);

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_Quit();
}


void renderSprite(int x, int y, SDL_Rect* clip)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, textWidth, textHeight };

    //Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopy(gRenderer, gSpriteSheetTexture, clip, &renderQuad);
}