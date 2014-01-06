/****************************************************************************************************************************
*Module Description: The Timer.cpp just handles the timer which handles the framerate and updates of everything on screen.	*
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
#include "Timer.h"
//***********************************************************
//Constructor - set initial variables etc...				*
//***********************************************************
Timer::Timer()
{
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}
//***********************************************************
//start - start timer by getting ticks via SDL				*
//***********************************************************
void Timer::start()
{
	//Start the timer
	started = true;
	//Unpause the timer
	paused = false;
	//Get the current clock time
	startTicks = SDL_GetTicks();
}
//***********************************************************
//stop - end the timer										*
//***********************************************************
void Timer::stop()
{
	//Stop the timer
	started = false;
	//Unpause the timer
	paused = false;
}
//***********************************************************
//pause - pause the timer									*
//***********************************************************
void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;
        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}
//***********************************************************
//unpause - restart timer									*
//***********************************************************
void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}
//***********************************************************
//get_ticks - returns the current time minus start time		*
//***********************************************************
int Timer::get_ticks()
{
	//If the timer is running
	if( started == true )
	{
		//If the timer is paused
		if( paused == true )
		{
			//Return the number of ticks when the timer was paused
			return pausedTicks;
		}
		else
		{
		//Return the current time minus the start time
		return SDL_GetTicks() - startTicks;
		}
	}
	//If the timer isn't running
	return 0;
}
//***********************************************************
//is_started - returns the status of boolean started		*
//***********************************************************
bool Timer::is_started()
{
    return started;
}
//***********************************************************
//is_paused - returns the status of boolean paused			*
//***********************************************************
bool Timer::is_paused()
{
    return paused;
}