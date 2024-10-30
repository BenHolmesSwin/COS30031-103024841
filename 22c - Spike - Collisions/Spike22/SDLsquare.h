#pragma once

#include <SDL.h>

//Screen dimension constants
extern const int SQUARE_SCREEN_WIDTH;
extern const int SQUARE_SCREEN_HEIGHT;

//window and background image
extern SDL_Window* sWindow;
extern SDL_Surface* sScreenSurface;

//renderer
extern SDL_Renderer* sRenderer;

void SDLsquare();
bool squareInit();
bool squareLoadMedia();
void squareClose();