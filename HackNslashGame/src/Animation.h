#ifndef ANIMATION
#define ANIMATION

#include "frame.h"

class Animation
{
public:
	string name;
	list<Frame> frames;

	Animation(string name = "");

	int GetNextFrameNumber(int frameNumber);
	Frame* GetNextFrame(Frame* frame);
	int GetEndFrameNumber();
	Frame* GetFarame(int frameNumber);

	void LoadAnimation(ifstream& file, list<DataGroupType>& groupTypes);
};
#endif