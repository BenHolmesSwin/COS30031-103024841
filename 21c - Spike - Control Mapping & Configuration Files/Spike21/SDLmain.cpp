//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <random>
#include <fstream>
#include <string>
#include <iostream>

//Screen dimension constants
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 800;

SDL_Keycode changeBackground;

std::vector<std::string> split(std::string& s, const std::string& delimiter) {// split tokens
	std::vector<std::string> tokens;
	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		tokens.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	tokens.push_back(s);

	return tokens;
}

//the file is read line by line with format "key: function" (only change background and bindings done)
void loadKey(char* fileName) {
	std::cout << "File Loaded" << std::endl;
	std::ifstream file;
	file.open(fileName);
	std::string line;
	while (!file.eof()) {//this assumes that the key is a lowercase letter so that it can use the ASCII value to map to the correct SDL_keycode
		std::getline(file,line);
		auto tokens  = split(line, ": ");
		char buffer[100];
		strcpy_s(buffer, tokens[0].data());
		if (tokens[1] == "change background") {
			changeBackground = int(buffer[0]);
			std::cout << "Change Background is currently: " << buffer[0] << std::endl;
		}
	}
	std::cout << "Reset Bindings is currently: p" << std::endl;
}

void changeKeys(SDL_Keycode key) {//this just hardcodes it to space and t, could make it randomise with a bit of difficulty
	changeBackground = key;
	std::cout << "Change Background is currently: " << (char)key << std::endl;
	std::cout << "Reset Binding is currently: p" << std::endl;
}

void changeBackgroundColor(SDL_Window* window, SDL_Surface* surface) {
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, rand() % 255, rand() % 255, rand() % 255));
	SDL_UpdateWindowSurface(window);
}

int main( int argc, char* args[] )
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//initalise random seed
	srand(time(NULL));

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface( window );

			//Fill the surface white
			SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0,255, 14));
			
			//Update the surface
			SDL_UpdateWindowSurface( window );
            
            //Hack to get window to stay up
            SDL_Event e;
			bool quit = false;
			loadKey(args[1]);
			while (quit == false) {
				while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN) {
						if (e.key.keysym.sym == changeBackground) {
							changeBackgroundColor(window, screenSurface);
						}
						else if (e.key.keysym.sym == SDLK_p) {
							loadKey(args[1]);
						}
						else {
							//changeKeys(e.key.keysym.sym);
						}
					}
				}
			}
		}
	}

	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}
	
