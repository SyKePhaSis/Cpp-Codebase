#ifndef WINDOW_H
#define WINDOW_H

//INCLUDES
#include "../Libraries/RayLib/include/raylib.h"
#include "stdbool.h"

//STRUCTS
typedef struct 
{
    int width;
    int height;
    const char *title;
} Window;

//FUNCTION DEFINITIONS
void InitWin(Window win, int frameRate);

//FUNCTIONS
void InitWin(Window win, int frameRate)
{
    InitWindow(win.width, win.height, win.title);
    SetTargetFPS(frameRate);
}

#endif 