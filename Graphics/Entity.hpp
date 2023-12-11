#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <cstdio>
#include <string>
#include <cstdbool>
#include "Core/Animation.hpp"
#include "Core/TextureLoader.hpp"
#include "Core/Collisions.hpp"

class Entity {
    public:
        std::string name;
        int id;
        Vector2 pos = (Vector2){0.0f, 0.0f};
        Vector2 size;
        bool direction;
        int tid;
        bool isSelected;
        TextureList *tl;
        Animations::CharacterAnimation ca;
        Collisions::EntityCollision ec;
        Collisions::List::Borders* clb;

        //Constructors

        Entity(void){}

        Entity(std::string n, int eid, Vector2 eSize, Collisions::List::Borders *clbp)
        {
            name = n;
            id = eid;
            size = eSize;
            tid = -1;
            ec = Collisions::EntityCollision((Rectangle){pos.x, pos.y, size.x, size.y});
            clb = clbp;
        }

        Entity(std::string n, int eid, Vector2 eSize, TextureList *tlp, const char* path, Collisions::List::Borders* clbp)
        {
            name = n;
            id = eid;
            size = eSize;
            AttachTextureList(tlp);
            AttachTexture(path);
            ec = Collisions::EntityCollision((Rectangle){pos.x, pos.y, size.x, size.y});
            clb = clbp;
        }

        virtual void UpdateMovement(void){}
        virtual void SetAnimation(void){}

        //Textures

        void AttachTextureList(TextureList *tlp)
        {
            tl = tlp;
        }

        void AttachTexture(const char* path)
        {
            tid = tl->LoadTextureToList(path);
        }

        //Animations

        void LoadAnimationsFromFile(const char* path)
        {
            ca.loadFromAssetFile(tl,path);
        }

        //Collisions

        void UpdateCollision(void)
        {
            ec.rect = (Rectangle){pos.x, pos.y, ec.rect.width, ec.rect.height};
        }

        void DrawCollision(void)
        {
            ec.DrawBorder();
        }

        void CheckCollision()
        {
            for(int j = 0; j < (int)clb->size; j++)
            {
                ec.CheckCollision(clb->cb[j].rect, &pos);
            }
        }

        //Update

        void update(void)
        {
            this->UpdateMovement();
            this->UpdateCollision();
            this->CheckCollision();
            if(ca.AnimationsLoaded)
            {
                ca.updateAnimation();
            }
        }

        //Rendering

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
