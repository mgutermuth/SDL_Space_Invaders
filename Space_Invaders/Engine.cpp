/****************************************************************************************************************************
*Module Description: The Engine.cpp basically runs through the instantiation and looping of the entire game.				*
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

int Engine::enemiesLeft = 0;
//********************************************************
//Constructor should set initial variables etc...        *
//********************************************************
Engine::Engine()
{
	//Set all surfaces that will be used/loaded to NULL initially
	screen=NULL;
	playerSprite=NULL;
	enemy1Sprite=NULL;
	enemy2Sprite=NULL;
	enemy3Sprite=NULL;
	lifeSprite=NULL;
	gameOverSprite=NULL;
	playerBulletSprite=NULL;
	backgroundSprite=NULL;
	scoreSprite=NULL;
	title=NULL;
	enemyBulletSprite=NULL;
	//Variables specific to Engine
	font=NULL;//Our font
	
	isLoaded=false;//to check if files were loaded already
	score=0;//set initial score to 0
	bgX=0;//background offset X
	bgY=0;//background offset Y
	backgroundSpeed=4;//background speed
	
	//Set screen up
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
	doShoot=false;
	//Call initScreen to do the actual creation of the screen
	initScreen();
	loop();
}
//********************************************************
//initScreen - initialze the screen                      *
//********************************************************
bool Engine::initScreen()
{
	//Checks if screen has been created
	if( screen == NULL )
    {
        return false;
    }
	//Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }
	//Initialize SDL_ttf
	if( TTF_Init() == -1 )
	{
		return false;
	}
	//Everything's OK
	SDL_WM_SetCaption( "Space Invaders", NULL);

	return true;
	
}	
//********************************************************
//load_files - Load all the images needed, then check to *
//			   see if all images were loaded correctly.  *
//********************************************************
bool Engine::load_files()
{	
	//Load up images
    playerSprite=load_image("player.bmp");
	enemy1Sprite=load_image("enemy1.bmp");
	enemy2Sprite=load_image("enemy2.bmp");
	enemy3Sprite=load_image("enemy3.bmp");
	lifeSprite=load_image("life.bmp");
	gameOverSprite=load_image("game_over.bmp");
	playerBulletSprite=load_image("bullet.bmp");
	backgroundSprite=load_image("background.bmp");
	title=load_image("game_start.bmp");
	gamewinSprite=load_image("game_win.bmp");
	enemyBulletSprite=load_image("enemyBullet.bmp");
	font = TTF_OpenFont( "invaderFont.ttf", 16 );

	//If there was a problem in loading any images
	if(playerSprite==NULL)
		return false;
	if(enemy1Sprite==NULL)
		return false;
	if(enemy2Sprite==NULL)
		return false;
	if(enemy3Sprite==NULL)
		return false;
	if(lifeSprite==NULL)
		return false;
	if(gameOverSprite==NULL)
		return false;
	if(playerBulletSprite==NULL)
		return false;
	if(backgroundSprite==NULL)
		return false;
	if(title==NULL)
		return false;
	if(enemyBulletSprite==NULL)
		return false;
	if(gamewinSprite==NULL)
		return false;

    //If everything loaded fine
	isLoaded=true;
    return true;
}
//********************************************************
//apply_surface - this is used to put any surface onto   *
//				  essentially any part of the screen,    *
//				  taking SDL_Surface*'s as arguements.   *
//********************************************************
void Engine::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;

    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;
	
    //Blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}
//********************************************************
//load_image - function to load images into game by      *
//			   returning an optimized SDL_Surface.	     *
//********************************************************
SDL_Surface *Engine::load_image( std::string filename )
{
    //The image that's loaded
	SDL_Surface* loadedImage = NULL; 
    //The optimized surface that will be used
	SDL_Surface* optimizedImage = NULL;    
    //Load the image
	loadedImage = IMG_Load(filename.c_str());

    //If the image loaded
    if( loadedImage != NULL )
    {
		//Create an optimized surface
        optimizedImage = SDL_DisplayFormat(loadedImage);
        //Free the old surface
		SDL_FreeSurface( loadedImage );
        //If the surface was optimized
		if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF));
        }
    }
    return optimizedImage;//Return the optimized surface
}
//********************************************************
//loop - Does some initializing by loading images and    *
//		 player variables, then loops continuously until *
//		 the player quits.								 *
//********************************************************
void Engine::loop()
{
	//***********************************
	//Initializers - do local variables	*
	//				 and loading here.	*
	//***********************************
		//Load the files
		if(isLoaded==false)
		{
			if( load_files() == false )
			{
				exit(-2);
			}
		}
		//Holds # of lives left for player
		int livesHolder=0;
		//Our score variable
		score=0;
		//Player instance
		Player* player1= new Player();
		//Timer instance
		Timer* fps=new Timer();
		while(player1->gameStart==false)
		{
			apply_surface(0,0,title,screen);
			player1->handleEvent();
			SDL_Flip(screen);

		}
//game start here


		//Enemy instance as an array
		Enemy enemies[ER][EC];
		Enemy::enemySpeed=1;
		enemiesLeft = ER*EC;
		//Set enemy positions
		for(int r=0; r<ER; r++)
		{
			for(int c=0; c<EC; c++)
			{
				enemies[0][c].enemyType=3;
				enemies[0][c].pointVal=100;
				enemies[0][c].enemyBox.w=21;
				enemies[0][c].enemyBox.h=21;

				enemies[1][c].enemyType=2;
				enemies[1][c].pointVal=70;
				enemies[1][c].enemyBox.w=28;
				enemies[1][c].enemyBox.h=20;
					if(r>1)
					{
						enemies[r][c].enemyBox.w=28;
						enemies[r][c].enemyBox.h=18;
					}

				//else they just will auto be type 1
				enemies[r][c].setPos((c+1)*45, r*35+35);
			}
		}
		char buf[10];
		SDL_Color fontColor = { 255, 255, 255,255 };
		

	//***********************************
	//Game Loop - This will loop until	*
	//			  the player quits.		*
	//***********************************
		while( !player1->getQuit() )
		{
			//livesHolder set to hold player lives
			livesHolder=player1->getLives();
			//Handle input via player
			player1->handleEvent();
			//Start the frame timer
			fps->start();
			itoa(score, buf, 10);
			//Render the text
			scoreSprite = TTF_RenderText_Solid( font, buf, fontColor);//buf
			//Scroll background
			bgY += backgroundSpeed;

			//If the background has gone too far
			if( bgY >= backgroundSprite->h )
			{
				//Reset the offset
				bgY = 0;
			}
			apply_surface( bgX, bgY, backgroundSprite, screen );
			apply_surface( bgX, bgY - backgroundSprite->h, backgroundSprite, screen );
			apply_surface( 5, 5, scoreSprite, screen );
			SDL_FreeSurface(scoreSprite);
			
			//If player is dead
			if(livesHolder==0)
			{
				//Show gameover at center of screen
				apply_surface((SCREEN_WIDTH/2)-gameOverSprite->w/2,(SCREEN_HEIGHT/2)-gameOverSprite->h/2,gameOverSprite,screen);
				switch(player1->replay)
				{
				case 0:
					quit_game();
					break;
				case 1:
					Enemy::enemySpeed=1;
					delete player1;
					delete fps;
					loop();
					break;
				case -1:
					//This is just default loop value to keep the game going.
					break;
				default:
					exit(-5);//Just to keep it safe
				}
			}
			//If player is not dead
			//Do player move, shoot, and display if player isn't dead (lives>0)
			else if(livesHolder!=0)
			{
				player1->move();
				//If player is shooting, apply the bullet sprite and call player shoot
				if(player1->getShoot())
				{
					apply_surface(player1->getBullX(), player1->getBullY(), playerBulletSprite,screen);
					player1->shoot();
				}
				if(enemiesLeft==0)
				{
					apply_surface(0,0,gamewinSprite,screen);
				}
			//***********************
			//Start Enemy Code		*
			//***********************
				//Checks direction enemies should move and sets movement variables
				for(int r=0; r<ER; r++)
				{
					for(int c=0; c<EC; c++)
					{
						// Sets direction all enemies should move and signals direction change and moving down
						if(enemies[r][c].isAlive==true)
						{
							enemies[r][c].setDirec();
						}
					}
				}
					if(enemiesLeft<35&&enemiesLeft>20)
					{

						Enemy::enemySpeed=3;

					}
					if(enemiesLeft<20&&enemiesLeft>5)
					{

						Enemy::enemySpeed=5;

					}
					if(enemiesLeft<2)
					{

						Enemy::enemySpeed=8;

					}
				//Moves each enemy based on current static xVel value
				for(int r=0; r<ER; r++)
				{
					for(int c=0; c<EC; c++)
					{
						enemies[r][c].move();
						if(enemies[r][c].isAlive==true){
							if(enemies[r][c].y>620)
								player1->lives=0;
						if(checkCollision(player1->getPlayerBox(),enemies[r][c].enemyBox)==true)
						{
							enemies[r][c].~Enemy();
							enemiesLeft--;
							player1->lives-=1;
						}
						}
					}
				}
				Enemy::needMoveDown = false; // Sets the need to move down false after every enemy has shifted down 

				// Show new enemy locations
				for(int r=0; r<ER; r++)
				{
					for(int c=0; c<EC; c++)
					{
						// Shows each enemy at their specific locations, if they are alive
						if(enemies[r][c].isAlive==true)
						{
							if(player1->getShoot())
							{
								if(checkCollision(player1->getBullBox(),enemies[r][c].enemyBox)==true)
								{
									enemies[r][c].~Enemy();
									enemiesLeft--;
									player1->shooting=false;
									score+=enemies[r][c].pointVal;
								}
							}
							if(enemies[r][c].enemyType==3)
							apply_surface(enemies[r][c].x,enemies[r][c].y,enemy3Sprite,screen);
							if(enemies[r][c].enemyType==2)
							apply_surface(enemies[r][c].x,enemies[r][c].y,enemy2Sprite,screen);
							if(enemies[r][c].enemyType==1)
							apply_surface(enemies[r][c].x,enemies[r][c].y,enemy1Sprite,screen);
						}
					}
				}


				//******************
				//Makes Enemy shoot*
				//******************
			
				for(int Col = 0; Col <11 ; Col++)
				{
					for (int Row = 4; Row >0; Row--)
					{
						
						if(enemies[Row][Col].isAlive == true)
						{
						
							enemies[Row][Col].setRand();

							if(enemies[Row][Col].isShooting==false){
								enemies[Row][Col].EShoot(Col, Row);
								//
							}
							if(enemies[Row][Col].isShooting == true)
							{
								//enemies[Row][Col].setBullX();
								doShoot=true;
								
							}
							
								Row = 0;
			         	}//end isAlive
							
						
					} //end for loop of Row
					
				}//end for loop of Col

				if(doShoot==true)
				{
					for(int Col=0;Col<11;Col++)
					{
						for(int Row=4;Row>0;Row--)
						{
							if(enemies[Row][Col].isShooting==true)
							{
							apply_surface(enemies[Row][Col].getBullX(),enemies[Row][Col].getBullY(),enemyBulletSprite,screen);
							enemies[Row][Col].moveEBull();
							}
							if(checkCollision(player1->getPlayerBox(),enemies[Row][Col].ebullBox)==true)
							{
								while(enemies[Row][Col].isShooting==true)
								{
									player1->lives--;
									enemies[Row][Col].isShooting=false;
									doShoot=false;
								}

							}
						if(enemies[Row][Col].BullY>600)
						{
							doShoot=false;
							enemies[Row][Col].isShooting=false;
						}
							
						}
					}
				}


			//***********************
			//End Enemy Code		*
			//***********************
			}

			//Display player
			apply_surface(player1->getX(),player1->getY(),playerSprite,screen);

			//Display lives
			for(int i=livesHolder;i>0;i--)
			{
				apply_surface(SCREEN_WIDTH-(i*35),10,lifeSprite,screen);
			}

			//Update the screen
			if( SDL_Flip( screen ) == -1 )
			{
				exit(-3);
			}

			//Cap the frame rate
			if( fps->get_ticks() < 1000 / fps->getFPS() )
			{
				SDL_Delay( ( 1000 / fps->getFPS() ) - fps->get_ticks() );

			}
			
		}
		//When quit is true we need to clean up and close program
		quit_game();
}
//********************************************************
//checkCollision - takes two rectangles and returns		 *
//				   whether or not they collide.			 *
//********************************************************
bool Engine::checkCollision(SDL_Rect A, SDL_Rect B)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;
	//Calculate the sides of rect A
	leftA = A.x;
	rightA = A.x + A.w;
	topA = A.y;
	bottomA = A.y + A.h;
	//Calculate the sides of rect B
	leftB = B.x;
	rightB = B.x + B.w;
	topB = B.y;
	bottomB = B.y + B.h;

	//If any of the sides from A are outside of B
	if( bottomA <= topB ) { return false; }
	if( topA >= bottomB ) { return false; }
	if( rightA <= leftB ) { return false; }
	if( leftA >= rightB ) { return false; }
	//If none of the sides from A are outside B
	return true;
}
//********************************************************
//quit_game - free up all surfaces used, and quit SDL.   *
//********************************************************
void Engine::quit_game()
{
    //Free surfaces...
    SDL_FreeSurface(playerSprite);
	SDL_FreeSurface(enemy1Sprite);
	SDL_FreeSurface(enemy2Sprite);
	SDL_FreeSurface(enemy3Sprite);
	SDL_FreeSurface(lifeSprite);
	SDL_FreeSurface(gameOverSprite);
	SDL_FreeSurface(backgroundSprite);
	SDL_FreeSurface(enemyBulletSprite);
	SDL_FreeSurface(screen);

	TTF_CloseFont( font );
	//Quit SDL_ttf
	TTF_Quit(); 
	//Quit SDL
	SDL_Quit();
	//Exit, with the most success
	exit(0);
}