#ifndef PLAYER_H
#define PLAYER_H
/****************************************************************************************************************************
*Module Description: The Player.h basically holds all of the inputs and player characteristics, controls,					*
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

class Player
{
private:
	static const int PLAYER_WIDTH = 60;
	static const int PLAYER_HEIGHT = 37;
	int x, y, xVel, yVel, xB, yB;
	SDL_Event event;
	bool quit;
	int lives;
	bool shooting;
	SDL_Rect bullBox;
	SDL_Rect playerBox;
	int bulletSpeed;
public:
	Player();
	SDL_Rect getBullBox(){return bullBox;};
	SDL_Rect getPlayerBox(){return playerBox;};
	bool getShoot(){return shooting;}
	int getLives(){return lives;}
	int getX(){return x;}
	int getY(){return y;}
	int getBullX() {return xB;};
	int getBullY() {return yB;};
	void setBullY();
	void setBullX();
	friend class Engine;
	bool getQuit();
	void handleEvent();
	int replay;
	bool gameStart;
	void move();
	void shoot();
};
#endif //PLAYER_H