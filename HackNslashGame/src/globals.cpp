#include "globals.h"

// math helpers
const float Globals::PI = M_PI;

// usefull for dev
bool Globals::debugging = true;

// sdl related	
int Globals::screenWidth = 640, Globals::screenHeight = 352, Globals::screenScale = 2;
SDL_Renderer* Globals::renderer;