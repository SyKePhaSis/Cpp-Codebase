#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <cstdio>
#include <string>
#include <cstdbool>
#include "Core/Animation.hpp"
#include "Core/TextureLoader.hpp"

class Entity {
    public:
        std::string name;
        int id;
        Vector2 pos;
        Vector2 size;
        int tid;
        Animations::CharacterAnimation ca;
        bool isSelected;
        TextureList *tl;

        Entity(std::string n, int eid, Vector2 eSize)
        {
            name = n;
            id = eid;
            size = eSize;
            ca = Animations::CharacterAnimation();
            tid = -1;
        }

        Entity(std::string n, int eid, Vector2 eSize, TextureList *tlp, const char* path)
        {
            name = n;
            id = eid;
            size = eSize;
            AttachTextureList(tlp);
            AttachTexture(path);
        }

        void SetPos(Vector2 Vpos)
        {
            pos = Vpos;
        }

        void SetSize(Vector2 Vsize)
        {
            size = Vsize;
        }

        void AttachTextureList(TextureList *tlp)
        {
            tl = tlp;
        }

        void AttachTexture(const char* path)
        {
            tid = tl->LoadTextureToList(path);
        }

        void LoadAnimationsFromFile(const char* path)
        {
            ca.loadFromAssetFile(tl,path);
        }

        void update(void)
        {
            if(ca.AnimationsLoaded)
            {
                ca.updateAnimation();
            }
        }

        void RenderStatic(void)
        {
            if(tid != -1)
            {
                Texture2D t  = tl->getTextureFromId(tid);
                DrawTextureV(t, pos, WHITE);
            }
        }

        void Render(void)
        {
            if(ca.AnimationsLoaded)
            {
                Rectangle crop_pos = ca.getAnimTextureCropPos();
                crop_pos.width *= size.x;
                crop_pos.height *= size.y;
                crop_pos.x *= size.x;
                Texture2D t = tl->getTextureFromId(ca.tidarray[ca.index]);
                DrawTextureRec(t ,crop_pos, pos, WHITE);
            } else
            {
                RenderStatic();
            }
        }

    private:

        void changeId(int eid)
        {
            id = eid;
        }


};
#endif
