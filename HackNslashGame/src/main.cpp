#include "includes.h"


int main(int argc, char** agv)
{
	//steup SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "error initialising SDL\n";
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("HacnNslashGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 352, SDL_WINDOW_SHOWN);

	//setup window
	if (window == nullptr)
	{
		SDL_Quit();
		cout << "Window Error\n";
		return 1;
	}

	//setup renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		cleanup(window);
		SDL_Quit();
		cout << "Renderer error\n";
		return 1;
	}

	// this is teh size to draw things at, before we sacle it to the screen size dimensions mentioned in createWindow
	SDL_RenderSetLogicalSize(renderer, 640, 352);

	//initialise sdl_image
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		SDL_Quit();
		cout << "sdl image did not initialise\n";
		return 1;
	}

	//init text to font
	if (TTF_Init() != 0)
	{
		SDL_Quit();
		cout << "ttf not init\n";
		return 1;
	}

	//init sdl mixer
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		SDL_Quit();
		cout << "mixer not init\n";
	}

	//load up a texture to draw
	string resPath = getResourcePath();
	SDL_Texture* texture = loadTexture(resPath + "map.png", renderer);

	//run game for 5000 ticks

	while (SDL_GetTicks() < 5000)
	{
		//clear the screen
		SDL_RenderClear(renderer);
		//draw what we want to the screen
		renderTexture(texture, renderer, 0, 0);
		// show image we've been rendering
		SDL_RenderPresent(renderer);
	}

	cleanup(renderer);
	cleanup(window);
	cleanup(texture);

	SDL_Quit();
	return 0;
}