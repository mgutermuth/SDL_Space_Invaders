/****************************************************************************************************************************
*Module Description: The Player.cpp basically holds all of the inputs and player characteristics, controls,					*
*					 player collision, lives, x and y positions etc.														*
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
#include "Player.h"
//***********************************************************
//Constructor - set initial variables etc...				*
//***********************************************************
Player::Player() 
{
	x = (640/2-PLAYER_WIDTH/2);
	y = (480-PLAYER_HEIGHT);
	xVel = 0; yVel = 0; //Initialize the velocity
	quit=false;
	lives=3;
	replay=-1;
	gameStart=false;
	bullBox.w=2;
	bullBox.h=10;
	playerBox.w=PLAYER_WIDTH;
	playerBox.h=PLAYER_HEIGHT;
	playerBox.x=x;
	playerBox.y=y;
	bulletSpeed=28;
}
//***********************************************************
//getQuit - simple getter for use by Engine to find			*
//			whether the window X has been hit.				*
//***********************************************************
bool Player::getQuit()
{
	return quit;
}
//***********************************************************
//handleEvent - uses SDL_PollEvent to check the keyboard	*
//				and other events such as close window.		*
//***********************************************************
void Player::handleEvent()
{
	while(SDL_PollEvent(&event))
	{
		//If X has been clicked
		if( event.type == SDL_QUIT )
		{
			if(gameStart==true)
			quit= true;
		}
		//If a key was pressed
		else if( event.type == SDL_KEYDOWN )
		{
			switch( event.key.keysym.sym )
			{
				case SDLK_LEFT: xVel -= PLAYER_WIDTH / 4; break;
				case SDLK_RIGHT: xVel += PLAYER_WIDTH / 4; break;
				case SDLK_SPACE: if(shooting==false){setBullX(); setBullY(); shooting = true;} break;
				case SDLK_y: if(lives<=0)replay=1; break;
				case SDLK_n: if(lives<=0)replay=0; break;
				case SDLK_ESCAPE: quit=true; break;
				case SDLK_RETURN: gameStart=true; break;
			}
		}//end keydown

		//If a key was released
		else if( event.type == SDL_KEYUP )
		{
			switch( event.key.keysym.sym )
			{
				case SDLK_LEFT: xVel += PLAYER_WIDTH / 4; break;
				case SDLK_RIGHT: xVel -= PLAYER_WIDTH / 4; break;
			}
		}//end keyup
	}//end SDL_PollEvent
}
//***********************************************************
//move - move will check the bounds of the screen, and move	*
//		 the player based on the X velocity.				*
//***********************************************************
void Player::move()
{
	//Move the player left or right
    x += xVel;
	playerBox.x=x;
    //If the player went too far to the left or right
	if( ( x < 0 ) || ( x + PLAYER_WIDTH > Engine::SCREEN_WIDTH ) )
    {
        //move back
        x -= xVel;
    }
}
//***********************************************************
//shoot - creates an instance of bullet object at current	*
//		  x,y position of player (y is constant anyway)		*
//***********************************************************
void Player::shoot()
{
	bullBox.x=xB;
	bullBox.y=yB;
	yB-=bulletSpeed;//"speed" of bullet
	if(yB <= 4)
	{
		shooting = false;
	}
}
//***********************************************************
//setBullX - sets the bullet position to current player X	*
//			 + the offset									*
//***********************************************************
void Player::setBullX()
{
	xB = x + PLAYER_WIDTH/2;
}
//***********************************************************
//setBullY - sets the bullet position to current player Y	*
//			 + the offset									*
//***********************************************************
void Player::setBullY()
{
	yB = y - 15;
}