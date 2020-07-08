#ifndef TIMECONTROLLER
#define TIMECONTROLLER

#include <iostream>
#include "includes.h"

class TimeController
{
public:
	static const int PLAY_STATE, PAUSE_STATE;

	int timeState;
	Uint32 lastUpdate;
	
	// delta time in seconds. Time since the last frame was rendered onto screen.
	float dT;
	
	TimeController();
	void UpdateTime(); // update lastUpdate and dT
	void Pause();
	void Resume();
	void Reset();

	static TimeController timeController;
};

#endif
