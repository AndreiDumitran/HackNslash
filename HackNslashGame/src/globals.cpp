#include "globals.h"

// math helpers
const float Globals::PI = M_PI;

// usefull for dev
bool Globals::debugging = true;

// sdl related	
int Globals::screenWidth = 640, Globals::screenHeight = 352, Globals::screenScale = 2;
SDL_Renderer* Globals::renderer;

string Globals::clipOffDataHeader(string data)
{
    int pos = data.find(":", 0);
    if (pos != -1)
        data = data.substr(pos + 1, data.length() - pos + 2);
    return data;
}
