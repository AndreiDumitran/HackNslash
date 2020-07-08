#include "TimeController.h"

const int TimeController::PLAY_STATE = 0, TimeController::PAUSE_STATE = 1;

TimeController::TimeController()
{
	dT = 0;
	lastUpdate = 0;
	timeState = PLAY_STATE;
}

void TimeController::UpdateTime()
{
	if (timeState = PAUSE_STATE) dT = 0;
	else
	{
		Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
		dT = timeDiff / 1000.0; // transform milliseconds to seconds;
	}
	lastUpdate = SDL_GetTicks();
}

void TimeController::Pause()
{
	timeState = PAUSE_STATE;
}

void TimeController::Resume()
{
	timeState = PLAY_STATE;
}

void TimeController::Reset()
{
	dT = 0;
	lastUpdate = SDL_GetTicks();
}

TimeController TimeController::timeController;