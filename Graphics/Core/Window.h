#pragma once
#ifndef WINDOW_H
#define WINDOW_H

//INCLUDES
#include "../../Libraries/RayLib/include/raylib.h"
#include <stdbool.h>
#include "Definitions.h"

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
void InitWin(Window *win);
void updateWin(Window *win);
void addCustomCursor(Window *win, const char* asset_text_file, Vector2 size);

//FUNCTIONS
void InitWin(Window *win)
{
    InitWindow(win->width, win->height, win->title);
    win->customCurs = 0;
    SetTargetFPS(FRAME_RATE);
}

void drawCursor(Window *win)
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
