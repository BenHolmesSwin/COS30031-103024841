#pragma once

class SDL_Rect;

void SDLgraphical();
bool graphInit();
bool graphLoadMedia();
void graphClose();
void renderSprite(int x, int y, SDL_Rect* clip);