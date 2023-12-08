#pragma once
#ifndef SPRITES_H
#define SPRITES_H

//VARIABLES
int sid = 0;

// INCLUDES
#include "../Libraries/RayLib/include/raylib.h"
#include "Core/Animation.hpp"
#include "Core/Definitions.hpp"
#include "Core/TextureLoader.hpp"

class Sprite {

    public:
        int id;
        Vector2 pos;
        int tid;
        TextureList *tl;

        Sprite(int id)
        {
            pos = (Vector2){0.0f, 0.0f};
        }

        Sprite(TextureList* tlp, int id, Vector2 Vpos, const char* texture_path)
        {
            AttachTextureList(tlp);
            tid = tl->LoadTextureToList(texture_path);
            pos = Vpos;
        }

        void AttachTextureList(TextureList *tlp)
        {
            tl = tlp;
        }

        void render(void)
        {
            Texture2D t = tl->getTextureFromId(tid);
            DrawTextureV(t, pos, WHITE);
        }
};

#endif
