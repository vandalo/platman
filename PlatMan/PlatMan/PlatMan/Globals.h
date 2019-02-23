#pragma once

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )

// Configuration -----------
#define SCREEN_SIZE 1
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FPS 30
#define FULLSCREEN false
#define VSYNC true
#define TITLE "TitleInglobals"
#define INTERMITENT_FAST 0.3
#define INTERMITENT_SLOW 0.5

enum ScreenType
{
	SCREEN,
	POPUP
};

// Useful typedefs ---------
typedef unsigned int uint;

// Deletes a buffer
#define RELEASE( x ) \
    {									  \
       if( x != nullptr )   \
       {						      \
         delete x;                  \
	     x = nullptr;             \
       }                      \
    }

// Deletes an array of buffers
#define RELEASE_ARRAY( x ) \
	{                              \
       if( x != nullptr )              \
       {                            \
           delete[] x;                \
	       x = nullptr;                    \
		 }                            \
                              \
	 }