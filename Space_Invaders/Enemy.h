#ifndef ENEMY_H
#define ENEMY_H
/****************************************************************************************************************************
*Module Description: The Enemy.h sets each enemy's statistics, its bounding box, the ability/ time when to shoot, and		*
*					 functionality to move etc.																				*
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

class Enemy
{
private:
	static const int ENEMY_WIDTH = 28;
	static const int ENEMY_HEIGHT = 28;
	int pointVal;
	int enemyType;//normal enemy
	int x, y; // x and y location of enemy
	int BullX, BullY; //value for bullet x and y
	int RandShoot; //int held for random
	static int xVel; // Holds x velocity of all enemies, static because always the same for each enemy
	static bool needMoveDown; // Holds if enemies need to move down
	bool isAlive;
	bool isShooting;
	static int enemySpeed;
	SDL_Rect enemyBox;//Box for collision detection
	SDL_Rect ebullBox;
public:
	Enemy(); // Arguments used to initialize enemy positions
	void setPos(int initX, int initY); // Sets initial position of enemy
	void setDirec(); // Checks for and sets which direction all enemies should be moving, return value signifies need to move down
	void move(); // Moves enemies left and right, and down if necessary
	~Enemy();
	friend class Engine;
	void EShoot(int Col, int Row);
	void setBullY(){BullY = y+ 40; ebullBox.y=y+40;};
	void setBullX(){BullX = x+ 12; ebullBox.x=x+12;};
	int getBullX(){return BullX ;};
	int getBullY() {return BullY ;};
	SDL_Rect getBullBox(){return ebullBox;};
	void setRand();
	int getRand(){return RandShoot;};
	void moveEBull();
};
#endif