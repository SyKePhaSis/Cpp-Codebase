#pragma once
#ifndef WINDOW_H
#define WINDOW_H

//INCLUDES
#include "Definitions.hpp"
#include "TextureLoader.hpp"
#include "../../Libraries/RayLib/include/raylib.h"

#include <string>

class Window {

    typedef struct
    {
        Vector2 size;
        int textId;
    } Cursor;

    public:
        int width;
        int height;
        bool customCurs;
        std::string title;

        Window(void){}

        Window(int w, int h, const std::string t) {
            width = w;
            height = h;
            title = t;
            customCurs = false;
            InitWindow(width, height, title.c_str());
            SetTargetFPS(60);
        }

        void SetParameters(int w, int h, const std::string t)
        {
            width = w;
            height = h;
            title = t;
            customCurs = false;
            InitWindow(width, height, title.c_str());
            SetTargetFPS(60);
        }

        void drawCursor(TextureList* tl){
            if(customCurs)
            {
                HideCursor();
                Texture2D t = tl->getTextureFromId(c.textId);
                DrawTextureV(t, GetMousePosition(), WHITE);
            }
        }

        void addCustomCursor(TextureList* tl, std::string asset_text_file, Vector2 size)
        {
            customCurs = true;
            c.size = size;
            c.textId = tl->LoadTextureToList(asset_text_file);
        }

    private:
        Cursor c;
};

#endif
