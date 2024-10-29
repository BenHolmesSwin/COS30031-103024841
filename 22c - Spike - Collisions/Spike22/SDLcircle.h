#pragma once

#include <SDL.h>

//Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

//window and background image
extern SDL_Window* cWindow;
extern SDL_Surface* cScreenSurface;

//renderer
extern SDL_Renderer* cRenderer;

void SDLcircle();
bool circleInit();
bool circleLoadMedia();
void circleClose();
