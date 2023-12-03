#ifndef WINDOW_H
#define WINDOW_H

//INCLUDES
#include "../Libraries/RayLib/include/raylib.h"
#include "stdbool.h"

//STRUCTS
typedef struct
{
    Vector2 size;
    Texture2D t;
} Cursor;

typedef struct
{
    int width;
    int height;
    const char *title;
    int customCurs;
    Cursor c;
} Window;

//FUNCTION DEFINITIONS
void InitWin(Window *win, int frameRate);
void updateWin(Window *win);
void addCustomCursor(Window *win, const char* asset_text_file, Vector2 size);

//FUNCTIONS
void InitWin(Window *win, int frameRate)
{
    InitWindow(win->width, win->height, win->title);
    win->customCurs = 0;
    SetTargetFPS(frameRate);
}

void updateWin(Window *win)
{
    if(win->customCurs)
    {
        DrawTextureV(win->c.t, GetMousePosition(),WHITE);
    }
}

void addCustomCursor(Window *win, const char* asset_text_file, Vector2 size)
{
    win->customCurs = 1;
    win->c.size = size;
    win->c.t = LoadTexture(asset_text_file);
}


#endif
