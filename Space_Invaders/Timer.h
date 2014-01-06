#ifndef TIMER_H
#define TIMER_H
/****************************************************************************************************************************
*Module Description: The Timer.h just handles the timer which handles the framerate and updates of everything on screen.	*
*																															*
*Author: Tyler Ortiz, Matt Gutermuth, Aaron Millet																			*
*																															*
*Date: December 17, 2009																									*
*																															*
*Revision History: - This was completed in one week-ish.																	*
*																															*
*Dependencies: <string>, "SDL/SDL.h", "SDL/SDL_image.h", "SDL/SDL_ttf.h", <stdlib.h>,										*
*			   "Player.h", "Enemy.h", "Timer.h"																				*
*****************************************************************************************************************************/

#include "Engine.h"

class Timer
{
private:
	static const int FRAMES_PER_SECOND = 15;
	//The clock time when the timer started
	int startTicks;
	//The ticks stored when the timer was paused
	int pausedTicks;
	//The timer status
	bool paused;
	bool started;
public:
	Timer();
	//The various clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	//Gets the timer's time
	int get_ticks();
	int getFPS(){return FRAMES_PER_SECOND;};
	//Checks the status of the timer
	bool is_started();
	bool is_paused();
};
#endif //TIMER_H