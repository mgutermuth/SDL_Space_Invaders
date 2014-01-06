/**************************************************
*   COPYRIGHTS © 2008 - FERRY YUWONO - FY - 081   *
**************************************************/

//The header
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>

//Font constant
#define GUI_FONT_TAHOMA "C:/WINDOWS/Fonts/TAHOMA.ttf"
#define GUI_FONT_VERDANA "C:/WINDOWS/Fonts/verdana.ttf"
#define GUI_FONT_ARIAL "C:/WINDOWS/Fonts/ARIAL.ttf"
#define GUI_FONT_TIMES "C:/WINDOWS/Fonts/TIMES.ttf"

//Screen attributes
const int SCREEN_BPP = 32;

//The surfaces
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;

bool shift = false;
bool capslock = false;
bool numlock = true;

//The Label
class Label
{
	protected :
	//X and Y Label
	int xText;
	int yText;

	//Rectangle of Label
    SDL_Rect box;

	//Font
	TTF_Font *font;

	//Font Color
	SDL_Color textColor;

	//Text Surface
	SDL_Surface *text;

	//Text
	char txt[101];

	//Length text
	int textLength;

	//MaxLength
	int maxLength;

	//Size Font
	int fontSize;

	public :
	//Constructor
	Label(int x, int y, char *caption, int sizeFont, int max, char *typeFont);

	//Destructor
	~Label();

	//Text Getter
	char* getText(){ return txt;}

	//Text Setter
	void setText(char *txt){
		if(textLength < 100 && textLength <= maxLength){
			strcpy_s(this->txt,sizeof(this->txt),txt);
			text = TTF_RenderText_Solid( font, this->txt, textColor );
			textLength = strlen(this->txt);
		}
	}

	//Append String to Text
	void putChar(char *chr){
		if(textLength < 100 && textLength+1 <= maxLength){
			strcat_s(this->txt,sizeof(this->txt),chr);
			text = TTF_RenderText_Solid( font, this->txt, textColor );
			textLength = strlen(this->txt);
		}
	}

	//BackSpace
	void backSpace(){
		this->txt[textLength-1]='\0';
		text = TTF_RenderText_Solid( font, this->txt, textColor );
		textLength = strlen(this->txt);
	}

	//Label handle Event
	void handle_events() {}

	//Shows the Label on the screen
    void show();
};

//The TextBox
class TextBox : public Label
{
	private :
	//TextBox Surface
	SDL_Surface *textBoxPicture;

	//Time
	int time;

	//Focused
	bool isFocused;

	public :
	//Constructor
	TextBox( int x, int y, int width, int height, char *caption, int sizeFont, int max, char *typeFont);

	//Destructor
	~TextBox();

	//TextBox handle Event
	void handle_events();

	//Shows the TextBox on the screen
	void show();
};

//The Button
class Button : public Label
{
    private:
	//The Button states
	static const int MOUSEUP = 0;
	static const int MOUSEOVER = 0;
	static const int MOUSEDOWN = 1;

	//Button Suface
	SDL_Surface *buttonPicture;

    //State of Button Animation
    SDL_Rect *status;

	//Button Animation
	SDL_Rect clip[2];

	//Pressed
	bool isPressed;

	//State of Button
	bool state;

    public:
	//Constructor
	Button( int x, int y, int width, int height, int xText, int yText, char *caption, int sizeFont, char *typeFont);

	//Destructor
	~Button();

    //Button handle Event
    void handle_events();

	bool isClicked();

    //Shows the Button on the screen
    void show();
};

void drawPixel(SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  Uint32 color = SDL_MapRGB(screen->format, R, G, B);
  switch (screen->format->BytesPerPixel)
  {
    case 1: // Assuming 8-bpp
      {
        Uint8 *bufp;
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
        *bufp = color;
      }
      break;
    case 2: // Probably 15-bpp or 16-bpp
      {
        Uint16 *bufp;
        bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x;
        *bufp = color;
      }
      break;
    case 3: // Slow 24-bpp mode, usually not used
      {
        Uint8 *bufp;
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x * 3;
        if(SDL_BYTEORDER == SDL_LIL_ENDIAN)
        {
          bufp[0] = color;
          bufp[1] = color >> 8;
          bufp[2] = color >> 16;
        } else {
          bufp[2] = color;
          bufp[1] = color >> 8;
          bufp[0] = color >> 16;
        }
      }
      break;
    case 4: // Probably 32-bpp
      {
        Uint32 *bufp;
        bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x;
        *bufp = color;
      }
      break;
  }
}

SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    //IMG_Load() can load BMP, PNM, XPM, LBM, PCX, GIF, JPEG, TGA and PNG files.
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0xD4, 0xD0, 0xC8 ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init(int Screen_Width, int Screen_Height, char *title)
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( Screen_Width, Screen_Height, SCREEN_BPP, SDL_SWSURFACE );

	//Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;
    }

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( title, NULL );

    //If everything initialized fine
    return true;
}

void clean_up()
{
	//Free the surfaces
	SDL_FreeSurface( screen );

    //Quit SDL
    SDL_Quit();
}

Label::Label(int xtxt, int ytxt, char *txt = "Label1", int size = 16, int max = 99, char *addFont = "C:/WINDOWS/Fonts/TAHOMA.ttf")
{
	//Copy txt to this->txt
	strcpy_s(this->txt,sizeof(this->txt),txt);

	//Validation
	this->txt[99]='\0';

	//Open the font
	font = TTF_OpenFont( addFont , size );

	//If there was an error in loading the font
    if( font == NULL ){
		//Use default font
        font = TTF_OpenFont( "C:/WINDOWS/Fonts/TAHOMA.ttf", size );
    }

	//Set textColor Black
	textColor.r = 0;
	textColor.g = 0;
	textColor.b = 0;

	//Render the text
	text = TTF_RenderText_Solid( font, this->txt, textColor );

	//Set the textLength
	textLength = strlen(this->txt);

	//Set the maxLength
	maxLength = max;

	//Set the fontSize
	fontSize = size;

	//Set X and Y text
	xText = xtxt;
	yText = ytxt;
}

void Label::show(){
	//Shows text on the screen
	apply_surface( xText, yText, text, screen );
}

Label::~Label(){
	//Free the Surface
	SDL_FreeSurface( text );

	//Close the font
	TTF_CloseFont( font );
}

TextBox::TextBox(int x,int y, int w, int h, char *txt = "Text1", int size = 16, int max = 99,char *addFont = "C:/WINDOWS/Fonts/TAHOMA.ttf")
:Label(x,y,txt,size,max,addFont){

	//Set the TextBox's Area
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;

    //Set the Time
	time = 0;

	//Set the textBoxPicture
	textBoxPicture = SDL_DisplayFormat( screen );

	//Set isFocused value
	isFocused = false;

	//Draws TextBox on textBoxPicture
	for(int i=0;i<w;i++){
		for(int j=0;j<h;j++){
			if((i==0 || j==0) && i!=w-1 && j!=h-1) drawPixel(textBoxPicture, x+i, y+j, 0x71, 0x6F, 0x64);
			else if(i==w-1 || j==h-1) drawPixel(textBoxPicture, x+i, y+j, 0xFF, 0xFF, 0xFF);
			else if((i==1 || j==1) && i!=w-2 && j!=h-2) drawPixel(textBoxPicture, x+i, y+j, 0x40, 0x40, 0x40);
			else if(i==w-2 || j==h-2) drawPixel(textBoxPicture, x+i, y+j, 0xD4, 0xD0, 0xC8);
		}
	}
}

void TextBox::handle_events(){
	//The mouse offsets
    int x = 0, y = 0;

	//If a mouse button was pressed
    if( event.type == SDL_MOUSEBUTTONDOWN ){
        //If the left mouse button was pressed
        if( event.button.button == SDL_BUTTON_LEFT ){
            //Get the mouse offsets
            x = event.button.x;
            y = event.button.y;

            //If the mouse is over the button
            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) ) isFocused = true;
			else isFocused = false;
		}
	}

	//If a keyboard was pressed
	if( event.type == SDL_KEYDOWN && isFocused){
		//Check the Key
        switch( event.key.keysym.sym ){
			case SDLK_BACKSPACE : backSpace(); break;
			case SDLK_LSHIFT : shift=true; break;
			case SDLK_RSHIFT : shift=true; break;
			case SDLK_CAPSLOCK : capslock=true; break;
			case SDLK_a: if(shift || capslock) putChar("A"); else putChar("a"); break;
			case SDLK_b: if(shift || capslock) putChar("B"); else putChar("b"); break;
			case SDLK_c: if(shift || capslock) putChar("C"); else putChar("c"); break;
			case SDLK_d: if(shift || capslock) putChar("D"); else putChar("d"); break;
			case SDLK_e: if(shift || capslock) putChar("E"); else putChar("e"); break;
			case SDLK_f: if(shift || capslock) putChar("F"); else putChar("f"); break;
			case SDLK_g: if(shift || capslock) putChar("G"); else putChar("g"); break;
			case SDLK_h: if(shift || capslock) putChar("H"); else putChar("h"); break;
			case SDLK_i: if(shift || capslock) putChar("I"); else putChar("i"); break;
			case SDLK_j: if(shift || capslock) putChar("J"); else putChar("j"); break;
			case SDLK_k: if(shift || capslock) putChar("K"); else putChar("k"); break;
			case SDLK_l: if(shift || capslock) putChar("L"); else putChar("l"); break;
			case SDLK_m: if(shift || capslock) putChar("M"); else putChar("m"); break;
			case SDLK_n: if(shift || capslock) putChar("N"); else putChar("n"); break;
			case SDLK_o: if(shift || capslock) putChar("O"); else putChar("o"); break;
			case SDLK_p: if(shift || capslock) putChar("P"); else putChar("p"); break;
			case SDLK_q: if(shift || capslock) putChar("Q"); else putChar("q"); break;
			case SDLK_r: if(shift || capslock) putChar("R"); else putChar("r"); break;
			case SDLK_s: if(shift || capslock) putChar("S"); else putChar("s"); break;
			case SDLK_t: if(shift || capslock) putChar("T"); else putChar("t"); break;
			case SDLK_u: if(shift || capslock) putChar("U"); else putChar("u"); break;
			case SDLK_v: if(shift || capslock) putChar("V"); else putChar("v"); break;
			case SDLK_w: if(shift || capslock) putChar("W"); else putChar("w"); break;
			case SDLK_x: if(shift || capslock) putChar("X"); else putChar("x"); break;
			case SDLK_y: if(shift || capslock) putChar("Y"); else putChar("y"); break;
			case SDLK_z: if(shift || capslock) putChar("Z"); else putChar("z"); break;
			case SDLK_1: if(shift || capslock) putChar("!"); else putChar("1"); break;
			case SDLK_2: if(shift || capslock) putChar("@"); else putChar("2"); break;
			case SDLK_3: if(shift || capslock) putChar("#"); else putChar("3"); break;
			case SDLK_4: if(shift || capslock) putChar("$"); else putChar("4"); break;
			case SDLK_5: if(shift || capslock) putChar("%"); else putChar("5"); break;
			case SDLK_6: if(shift || capslock) putChar("^"); else putChar("6"); break;
			case SDLK_7: if(shift || capslock) putChar("&"); else putChar("7"); break;
			case SDLK_8: if(shift || capslock) putChar("*"); else putChar("8"); break;
			case SDLK_9: if(shift || capslock) putChar("("); else putChar("9"); break;
			case SDLK_0: if(shift || capslock) putChar(")"); else putChar("0"); break;
			case SDLK_LEFTBRACKET: if(shift || capslock) putChar("{"); else putChar("["); break;
			case SDLK_RIGHTBRACKET: if(shift || capslock) putChar("}"); else putChar("]"); break;
			case SDLK_MINUS: if(shift || capslock) putChar("_"); else putChar("-"); break;
			case SDLK_QUOTE: if(shift || capslock) putChar("\""); else putChar("'"); break;
			case SDLK_SEMICOLON: if(shift || capslock) putChar(":"); else putChar(";"); break;
			case SDLK_SLASH: if(shift || capslock) putChar("?"); else putChar("/"); break;
			case SDLK_BACKSLASH: if(shift || capslock) putChar("|"); else putChar("\\"); break;
			case SDLK_COMMA: if(shift || capslock) putChar("<"); else putChar(","); break;
			case SDLK_EQUALS: if(shift || capslock) putChar("+"); else putChar("="); break;
			case SDLK_BACKQUOTE: if(shift || capslock) putChar("~"); else putChar("`"); break;
			case SDLK_PERIOD : if(shift || capslock) putChar(">"); else putChar("."); break;
			case SDLK_SPACE: putChar(" "); break;
			case SDLK_NUMLOCK : numlock=true; break;
			case SDLK_KP0: if(numlock) putChar("0"); break;
			case SDLK_KP1: if(numlock) putChar("1"); break;
			case SDLK_KP2: if(numlock) putChar("2"); break;
			case SDLK_KP3: if(numlock) putChar("3"); break;
			case SDLK_KP4: if(numlock) putChar("4"); break;
			case SDLK_KP5: if(numlock) putChar("5"); break;
			case SDLK_KP6: if(numlock) putChar("6"); break;
			case SDLK_KP7: if(numlock) putChar("7"); break;
			case SDLK_KP8: if(numlock) putChar("8"); break;
			case SDLK_KP9: if(numlock) putChar("9"); break;
			case SDLK_KP_PERIOD: if(numlock) putChar("."); break;
			case SDLK_KP_DIVIDE: putChar("/"); break;
			case SDLK_KP_MULTIPLY: putChar("*"); break;
			case SDLK_KP_MINUS: putChar("-"); break;
			case SDLK_KP_PLUS: putChar("+"); break;
		}
	}

	//If a keyboard was release
	if( event.type == SDL_KEYUP ){
		//Check the Key
		switch( event.key.keysym.sym ){
			case SDLK_LSHIFT: shift=false; break;
			case SDLK_RSHIFT: shift=false; break;
			case SDLK_CAPSLOCK: capslock=false; break;
			case SDLK_NUMLOCK : numlock=false; break;
		}
	}
}


void TextBox::show(){
	//Make temp surface
	SDL_Surface *temp = SDL_DisplayFormat( screen );

	//Set Area of text in textBox
	SDL_Rect boxTemp = { box.x + 2, box.y + 2, box.w - 4, box.h - 4 };

	//If focused
	if(isFocused){
		//Show the Sign
		if( time < 650 ){
			strcat_s(this->txt,sizeof(this->txt),"|");
			text = TTF_RenderText_Solid( font, this->txt, textColor );
		}
	}

	//Fill the temp surface with white color
	SDL_FillRect(temp, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );

	//Puts text on the temp surface
	apply_surface(box.x + 3, box.y + 2, text, temp );

	//Show textBox on the screen
	apply_surface(box.x, box.y, textBoxPicture, screen, &box);

	//Show text on the screen
	apply_surface(boxTemp.x, boxTemp.y, temp, screen, &boxTemp );

	//If focused
	if(isFocused){
		//Delete the Sign
		if( time < 650 ){
			this->txt[textLength]='\0';
			text = TTF_RenderText_Solid( font, this->txt, textColor );
		}

		//Increase the Time
		time++;

		//Set time to 0
		if( time == 1300 ) time=0;
	}

	//Free the temp surface
	SDL_FreeSurface( temp );
}

TextBox::~TextBox(){
	//Free textBoxPicture surface
	SDL_FreeSurface( textBoxPicture );
}

Button::Button( int x, int y, int w, int h, int xtxt, int ytxt, char *txt = "command1", int size = 16, char *addFont = "C:/WINDOWS/Fonts/TAHOMA.ttf")
:Label(xtxt,ytxt,txt,size,99,addFont)
{
    //Set the Button's Area
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;

    //Set the buttonPicture
	buttonPicture = SDL_DisplayFormat( screen );

	//Set isPressed value
	isPressed = false;

	//Set state value
	state = false;

	//Set the Animation Area
	for(int i=0;i<2;i++)
	{
		clip[i].x = 1;
		clip[i].y = 1 + i*h;
		clip[i].w = w;
		clip[i].h = h;
	}

	//Draw Button Up and Down Animation on buttonPicture
	for(int i=0;i<w;i++)
	{
		for(int j=0;j<h;j++)
		{
			if(i==0 || i==w-1 || j==0 || j==h-1)
			{
				drawPixel(buttonPicture, 1+i, 1+j, 0, 0, 0);			//Button Up
				drawPixel(buttonPicture, 1+i, h+1+j, 0, 0, 0);			//Button Down
			}
			else if((i==1 || j==1) && i!=w-2 && j!=h-2)
			{
				drawPixel(buttonPicture, 1+i, 1+j, 0xFF, 0xFF, 0xFF);	//Button Up
				drawPixel(buttonPicture, 1+i, h+1+j, 0xAC, 0xA8, 0x99);	//Button Down
			}
			else if(i==w-2 || j==h-2)
			{
				drawPixel(buttonPicture, 1+i, 1+j, 0x71, 0x6F, 0x64);	//Button Up
				drawPixel(buttonPicture, 1+i, h+1+j, 0xAC, 0xA8, 0x99);	//Button Down
			}
			else if((i==2 || j==2) && i!=w-3 && j!=h-3)
			{
				drawPixel(buttonPicture, 1+i, 1+j, 0xF1, 0xEF, 0xE2);	//Button Up
				drawPixel(buttonPicture, 1+i, h+1+j, 0xD4, 0xD0, 0xC8);	//Button Down
			}
			else if(i==w-3 || j==h-3)
			{
				drawPixel(buttonPicture, 1+i, 1+j, 0xAC, 0xA8, 0x99);	//Button Up
				drawPixel(buttonPicture, 1+i, h+1+j, 0xD4, 0xD0, 0xC8);	//Button Down
			}
			else
			{
				drawPixel(buttonPicture, 1+i, 1+j, 0xD4, 0xD0, 0xC8);	//Button Up
				drawPixel(buttonPicture, 1+i, h+1+j, 0xD4, 0xD0, 0xC8);	//Button Down
			}
		}
	}

	//Set the state Animation
    status = &clip[ MOUSEUP ];
}

bool Button::isClicked(){
	//Return the state value
	return state;
}

void Button::handle_events(){
    //The mouse offsets
    int x = 0, y = 0;

	//Set the state false
	state = false;

    //If the mouse moved
    if( event.type == SDL_MOUSEMOTION ){
        //Get the mouse offsets
        x = event.motion.x;
        y = event.motion.y;

        //If the mouse is over the button
        if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) ){
            //Set the Button State Animation
			if(!isPressed) status = &clip[ MOUSEOVER ];
			else status = &clip[ MOUSEDOWN ];
        }
        //If not MouseOut
        else
        {
            //Set the Button State Animation
            status = &clip[ MOUSEUP ];
			isPressed = false;
        }
    }
    //If a mouse button was pressed
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        //If the left mouse button was pressed
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            //Get the mouse offsets
            x = event.button.x;
            y = event.button.y;

            //If the mouse is over the button
            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
            {
                //Set the Button State Animation
                status = &clip[ MOUSEDOWN ];
				isPressed = true;
            }
        }
	}
    //If a mouse button was released
    if( event.type == SDL_MOUSEBUTTONUP )
    {
        //If the left mouse button was released
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            //Get the mouse offsets
            x = event.button.x;
            y = event.button.y;

            //If the mouse is over the button
            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) && isPressed)
            {
                //Set the Button State Animation
                status = &clip[ MOUSEUP ];
				isPressed = false;
				state = true;
            }
        }
    }
}

void Button::show(){
    //Make temp surface
	SDL_Surface *temp = SDL_DisplayFormat( screen );

	//Set Area of text in Button
	SDL_Rect boxTemp = { box.x + 3, box.y + 3, box.w - 6, box.h - 6 };

	//Fill the temp surface with white color
	SDL_FillRect(temp, &screen->clip_rect, SDL_MapRGB( screen->format, 0xD4, 0xD0, 0xC8 ) );

	//Puts text on the temp surface
	apply_surface( xText, yText, text, temp );

	//Show Button on the screen
	apply_surface( box.x, box.y, buttonPicture, screen, status );

	//Show text on the screen
	if(isPressed) apply_surface( boxTemp.x+1, boxTemp.y+1, temp, screen, &boxTemp );
	else apply_surface( boxTemp.x, boxTemp.y, temp, screen, &boxTemp );

	//Free the temp surface
	SDL_FreeSurface( temp );
}

Button::~Button(){
	//Free the buttonPicture surface
	SDL_FreeSurface( buttonPicture );
}

void clearWindow(){
	//Fill the screen with R=0xD4 G=0xD0 B=0xC8 color
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xD4, 0xD0, 0xC8 ) );
}