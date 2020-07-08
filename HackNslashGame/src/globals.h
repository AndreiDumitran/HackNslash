#ifndef GLOBALS
#define GLOBALS

#include "includes.h"

class Globals
{
public:
	// math helpers
	static const float PI;

	// usefull for dev
	static bool debugging;

	// sdl related	
	static int screenWidth, screenHeight, screenScale;
	static SDL_Renderer* renderer;
};

#endif