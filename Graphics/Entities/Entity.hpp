    #pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <cstdio>
#include <string>
#include <cstdbool>

#include "../Core/Animation.hpp"
#include "../Core/TextureLoader.hpp"
#include "../Core/Collisions.hpp"

class Entity {
    public:
        //Have to Assign
        std::string name;
        int id;
        Vector2 pos = (Vector2){0.0f, 0.0f};
        Vector2 size;
        std::shared_ptr<TextureList> tl;
        Animations::CharacterAnimation ca;
        Animations::ObjectAnimation selector;
        std::vector<Collisions::Border>* bv;

        //Auto Assign
        bool direction;
        int tid;
        bool isSelected;
        Collisions::EntityCollision ec;

        //Constructors

        Entity(void){}

        Entity(std::string n, Vector2 eSize, std::vector<Collisions::Border> *clbp)
        {
            name = n;
            size = eSize;
            tid = -1;
            ec = Collisions::EntityCollision((Rectangle){pos.x, pos.y, size.x, size.y});
            bv = clbp;
        }

        Entity(std::string n, Vector2 eSize, std::shared_ptr<TextureList> tlp, std::string path, std::vector<Collisions::Border>* clbp)
        {
            name = n;
            size = eSize;
            tl = tlp;
            this->AttachTexture(path);
            ec = Collisions::EntityCollision((Rectangle){pos.x, pos.y, size.x, size.y});
            bv = clbp;
        }

        virtual void UpdateMovement(void){}
        virtual void SetAnimation(void){}

        //Textures

        void AttachTextureList(TextureList &tlp)
        {
            tl = std::make_shared<TextureList>(tlp);
        }

        void AttachTexture(std::string path)
        {
            tid = tl->LoadTextureToList(path);
        }

        //Animations

        void LoadAnimationsFromFile(std::string path)
        {
            ca.loadFromAssetFile(tl.get(),path);
        }

        void AttachEntitySelector(std::string path)
        {
            selector = Animations::ObjectAnimation();
            std::ifstream fdata(path);
            if(!fdata)
            {
                printf("ERROR: Couldn't Load Entity Selector File [%s]\n", path.c_str());
            } else {
                char animpath[64];
                float fanimSpeed;
                int fanimLen;
                if(fdata >> animpath >> fanimSpeed >> fanimLen)
                {
                    selector.addAnimation(tl.get(),animpath,fanimSpeed,fanimLen);
                    printf("INFO: Entity Selector Added From File [%s]\n", path.c_str());
                }
            }
        }

        //EntitySelection
        void checkSelected(void)
        {
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Vector2 Mpos = GetMousePosition();
                if(CheckCollisionPointRec(Mpos, this->ec.rect))
                {
                    isSelected = true;
                } else
                {
                    isSelected = false;
                }
            }
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
            for(size_t j = 0; j < bv->size(); j++)
            {
                ec.CheckCollision(bv->at(j).rect, &pos);
            }
        }

        //Update

        void Update(void)
        {
            this->UpdateMovement();
            this->UpdateCollision();
            this->CheckCollision();
            this->checkSelected();
            if(isSelected)
            {
                this->selector.updateAnimation();
            }
            if(ca.AnimationsLoaded)
            {
                ca.updateAnimation();
            }
        }

        //Rendering

        void RenderSelector(void)
        {
            if(isSelected)
            {
                Rectangle r = selector.getAnimTextureCropPos();
                r.width = r.width * size.x;
                r.height = r.height * size.y;
                r.x = r.x * size.x;
                Texture2D t =  tl->getTextureFromId(selector.tId);
                DrawTextureRec(t, r, pos, WHITE);
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
                Texture2D t = tl->getTextureFromId(ca.tidarray.at(ca.index));
                DrawTextureRec(t ,crop_pos, pos, WHITE);
            } else
            {
                RenderStatic();
            }
            this->RenderSelector();
        }

        void changeId(int eid)
        {
            id = eid;
        }
};
#endif
