#ifndef FRAME
#define FRAME

#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include "SDL.h"
#include "drawing_functions.h"
#include "globals.h"
#include "groupBuilder.h"

class Frame
{
public:
	int frameNumber;
	SDL_Rect clip;
	float duration;
	SDL_Point offSet;

	list<Group*> frameData;

	void Draw(SDL_Texture* spriteSheet, float x, float y);

	void LoadFrame(ifstream& file, list<DataGroupType>& groupTypes);
};



#endif