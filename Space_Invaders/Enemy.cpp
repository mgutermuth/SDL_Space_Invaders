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
#include "Enemy.h"
//Static variables set up.
int Enemy::xVel=1;
bool Enemy::needMoveDown=false;
int Enemy::enemySpeed=1;
//***********************************************************
//Constructor - set each enemy to alive status				*
//***********************************************************
Enemy::Enemy()
{
	isAlive=true;
	enemyType=1;
	enemyBox.w=ENEMY_WIDTH;
	enemyBox.h=ENEMY_HEIGHT;
	ebullBox.w=2;
	ebullBox.h=10;
	ebullBox.x=x;
	ebullBox.y=y;
	enemySpeed=1;
	pointVal=50;
	BullX=0;
	BullY=0;
	isShooting=false;
}

//***********************************************************
//setPos - setter for our private x,y variables for enemy.	*
//***********************************************************
void Enemy::setPos(int initX, int initY)
{
	x = initX; // Sets initial x value to argument value
	y = initY; // Sets initial y value to argument value
	if(enemyType==1)//low enemy
	{
		enemyBox.x=x;
		enemyBox.y=y+4;
	}
	if(enemyType==2)//midd enemy
	{
		enemyBox.x=x;
		enemyBox.y=y+3;
	}
	if(enemyType==3)//top enemy
	{
		enemyBox.x=x+4;
		enemyBox.y=y+3;
	}
}
//***********************************************************
//setDirec - checks status of this enemy object to see if it*
//			 hits the bounds. Switches direction variable	*
//			 when a side is hit.							*
//***********************************************************
void Enemy::setDirec()
{
	if(x < 1)
	{
		// Sets enemy movement to the left
		xVel = enemySpeed;//-xVel
		needMoveDown = true; 
	}
	if(x > Engine::SCREEN_WIDTH-ENEMY_WIDTH-1)
	{
		xVel = -enemySpeed;
		needMoveDown=true;
	}
}
//***********************************************************
//move - change x position by enemy speed.					*
//***********************************************************
void Enemy::move()
{
	// Moves the enemies down if they need to
	if(needMoveDown == true)
	{
		y += ENEMY_HEIGHT;
	}
	x += xVel; // Moves enemies in current direction specified
	if(enemyType==1)//low enemy
	{
		enemyBox.x=x;
		enemyBox.y=y+4;
	}
	if(enemyType==2)//mid enemy
	{
		enemyBox.x=x;
		enemyBox.y=y+3;
	}
	if(enemyType==3)//top enemy
	{
		enemyBox.x=x+4;
		enemyBox.y=y+3;
	}
}
//***********************************************************
//EShoot - this is the function that tells the enemy to		*
//		   shoot, it shoots based on an algorithm via		*
//		   modulus.											*
//***********************************************************
void Enemy::EShoot(int Col, int Row)
{
	//Temporary variable to RandShoot
	int TmpVal = RandShoot;
	//If enemies are fewer, set shooting to true more often
	if(Engine::enemiesLeft<30)
	{
		if(TmpVal ==1||TmpVal==2)
		{
			isShooting = true;
			setBullY();
			setBullX();
		}
	}
	if (TmpVal == 1)
	{
		isShooting = true;
		setBullY();
		setBullX();
	}
}
//***********************************************************
//setRand - sets RandShoot integer to a random number,		*
//			based on how many enemies left on screen.		*
//***********************************************************
void Enemy::setRand()
{
	RandShoot = (rand() % (Engine::enemiesLeft*4)) + 1;
}
//***********************************************************
//moveEBull - move bullet while on screen. Also pulls along	*
//			  collision boxes.								*
//***********************************************************
void Enemy::moveEBull()
{
	BullY += 5;
	ebullBox.x=BullX;
	ebullBox.y=BullY;
	if(BullY >= 600)
	{
		isShooting = false;
	}
}
//***********************************************************
//Deconstructor - what happens when enemy has died.			*
//***********************************************************
Enemy::~Enemy()
{
	isAlive=false;
}