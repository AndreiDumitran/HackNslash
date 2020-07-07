#include "includes.h"

SDL_Window* window = SDL_CreateWindow("HacnNslashGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 352, SDL_WINDOW_SHOWN);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

void Initialisations()
{
	Log::Init();
	GAME_WARN("Initialising systems");
	//setup window
	if (window == nullptr)
	{
		SDL_Quit();
		SDL_FATAL("Window not initialised");
	}
	else SDL_INFO("Window successfully initialised");

	//setup renderer

	if (renderer == nullptr)
	{
		cleanup(window);
		SDL_Quit();
		SDL_FATAL("Renderer not initialised");
	}
	else SDL_INFO("Renderer successfully initialised");

	//initialise sdl_image
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		SDL_Quit();
		SDL_FATAL("SDL IMAGE not initialised");
	}
	else SDL_INFO("SDL IMAGE successfully initialised");

	//init text to font
	if (TTF_Init() != 0)
	{
		SDL_Quit();
		SDL_FATAL("SDL TTF not initialised");
	}
	else SDL_INFO("SDL TTF successfully initialised");

	//init sdl mixer
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		SDL_Quit();
		SDL_FATAL("SDL AUDIO not initialised");
	}
	else SDL_INFO("SDL AUDIO successfully initialised");
}

int main(int argc, char** agv)
{
	
	Initialisations();
	

	// this is teh size to draw things at, before we sacle it to the screen size dimensions mentioned in createWindow
	SDL_RenderSetLogicalSize(renderer, 640, 352);

	//load up a texture to draw
	string resPath = getResourcePath();
	SDL_Texture* texture = loadTexture(resPath + "map.png", renderer);


	GAME_WARN("Starting game!");
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
	GAME_WARN("Game closed!");
	cleanup(renderer);
	cleanup(window);
	cleanup(texture);

	SDL_Quit();
	return 0;
}