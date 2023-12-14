#pragma once
#ifndef SPRITES_H
#define SPRITES_H

// INCLUDES
#include "../Libraries/RayLib/include/raylib.h"
#include "Animation.hpp"
#include "Definitions.hpp"
#include "TextureLoader.hpp"

#include <memory>

class Sprite {

    public:
        int id;
        int tid;
        Vector2 pos;
        std::smart_ptr<TextureList> tl;

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
            tl = std::make_shared<TextureList>(tlp);
        }

        void Render(void)
        {
            Texture2D t = tl->getTextureFromId(tid);
            DrawTextureV(t, pos, WHITE);
        }
};

#endif
