#include "includes.h"

int main(int argc, char** agv)
{
	Log::Init();
	GAME_WARN("Initialising systems");
	
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)	SDL_FATAL("SDL not initialised.");
	else SDL_INFO("SDL initialised.");
		
	SDL_Window* window = SDL_CreateWindow("HacnNslashGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		Globals::screenWidth * Globals::screenScale, Globals::screenHeight * Globals::screenScale, SDL_WINDOW_SHOWN);
	//setup window
	if (window == nullptr)
	{
		SDL_Quit();
		SDL_FATAL("Window not initialised");
	}
	else SDL_INFO("Window successfully initialised");

	//setup renderer
	Globals::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (Globals::renderer == nullptr)
	{
		cleanup(window);
		SDL_Quit();
		SDL_FATAL("Renderer not initialised");
	}
	else SDL_INFO("Renderer successfully initialised");

	// this is the size to draw things at, before we sacle it to the screen size dimensions mentioned in createWindow
	SDL_RenderSetLogicalSize(Globals::renderer, Globals::screenWidth, Globals::screenHeight);

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
	
	//load up a texture to draw
	string resPath = getResourcePath();
	SDL_Texture* texture = loadTexture(resPath + "map.png", Globals::renderer);

	//run game for 5000 ticks
	GAME_WARN("Starting game!");
	while (SDL_GetTicks() < 5000)
	{
		//clear the screen
		SDL_RenderClear(Globals::renderer);
		//draw what we want to the screen
		renderTexture(texture, Globals::renderer, 0, 0);
		// show image we've been rendering
		SDL_RenderPresent(Globals::renderer);
		
	}
	GAME_WARN("Game closed!");
	cleanup(Globals::renderer);
	cleanup(window);
	cleanup(texture);

	SDL_Quit();
	return 0;
}