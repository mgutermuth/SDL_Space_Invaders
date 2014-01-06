#ifndef ENGINE_H
#define ENGINE_H
/****************************************************************************************************************************
*Module Description: The Engine.h basically runs through the instantiation and looping of the entire game.					*
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
//#include "SDL.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "Player.h"
#include "Timer.h"
#include "Enemy.h"
#include <stdlib.h>//for itoa
#include <string>

class Engine
{
private:
	static const int SCREEN_WIDTH = 640;//Screen width
	static const int SCREEN_HEIGHT = 480;//Screen height
	static const int SCREEN_BPP = 32;//Screen color depth, bits per pixel
	static const int ER = 5; // Number of enemy rows
	static const int EC = 11; // Number of enemy columns
	int bgX, bgY;//Background offsets
	int backgroundSpeed;
	static const int bgW = 640;
	static const int bgH = 480;
	//SDL Surfaces to hold images
	SDL_Surface* screen;
	SDL_Surface* playerSprite;
	SDL_Surface* enemy1Sprite;
	SDL_Surface* enemy2Sprite;
	SDL_Surface* enemy3Sprite;
	SDL_Surface* lifeSprite;
	SDL_Surface* gameOverSprite;
	SDL_Surface* playerBulletSprite;
	SDL_Surface* backgroundSprite;
	SDL_Surface* load_image(std::string);
	SDL_Surface* scoreSprite;
	SDL_Surface* title;
	SDL_Surface* gamewinSprite;
	SDL_Surface* enemyBulletSprite;
	TTF_Font *font;
	int score;
	static int enemiesLeft;
	bool doShoot;
public:
	Engine();
	bool initScreen();
	bool isLoaded;
	bool load_files();
	void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
	friend void Player::move();//to access SCREEN_WIDTH for bounds
	friend class Enemy;
	void loop();
	bool checkCollision(SDL_Rect,SDL_Rect);
	void quit_game();
};
#endif //ENGINE_H