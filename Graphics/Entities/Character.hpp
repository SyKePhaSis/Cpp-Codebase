#include "../../Libraries/RayLib/include/raylib.h"
#include "../Entity.hpp"

class Character : public Entity {

    public:

        Character(){}

        Character(std::string n, int eid, Vector2 eSize, std::vector<Collisions::Border> *clbp)
        {
            name = n;
            id = eid;
            size = eSize;
            tid = -1;
            ec = Collisions::EntityCollision((Rectangle){pos.x, pos.y, size.x, size.y});
            bv = clbp;
        }

        Character(std::string n, int eid, Vector2 eSize, TextureList *tlp, const char* path, std::vector<Collisions::Border>* clbp)
        {
            name = n;
            id = eid;
            size = eSize;
            AttachTextureList(tlp);
            AttachTexture(path);
            ec = Collisions::EntityCollision((Rectangle){pos.x, pos.y, size.x, size.y});
            bv = clbp;
        }

        void UpdateMovement(void)
        {
            int sprint = 0;
            int walk = 0;
            int AnimIndex = 0;
            if(IsKeyDown(KEY_LEFT_SHIFT))
            {
                if(IsKeyDown(KEY_W))
                {
                    pos.y -= CHARACTER_SPRINT_SPEED / FRAME_RATE;
                    sprint = 1;
                }
                if(IsKeyDown(KEY_A))
                {
                    pos.x -= CHARACTER_SPRINT_SPEED / FRAME_RATE;
                    sprint = 1;
                }
                if(IsKeyDown(KEY_S))
                {
                    pos.y += CHARACTER_SPRINT_SPEED / FRAME_RATE;
                    sprint = 1;
                }
                if(IsKeyDown(KEY_D))
                {
                    pos.x += CHARACTER_SPRINT_SPEED / FRAME_RATE;
                    sprint = 1;
                }
            }
            if(IsKeyDown(KEY_W))
            {
                pos.y -= CHARACTER_SPRINT_SPEED / FRAME_RATE;
                walk = 1;
            }
            if(IsKeyDown(KEY_A))
            {
                pos.x -= CHARACTER_SPRINT_SPEED / FRAME_RATE;
                walk = 1;
                direction = true;
            }
            if(IsKeyDown(KEY_S))
            {
                pos.y += CHARACTER_SPRINT_SPEED / FRAME_RATE;
                walk = 1;
            }
            if(IsKeyDown(KEY_D))
            {
                pos.x += CHARACTER_SPRINT_SPEED / FRAME_RATE;
                walk = 1;
                direction = false;
            }
            AnimIndex = sprint + walk;
            if(direction)
            {
                AnimIndex += 3;
            }
            ca.changeIndex(AnimIndex);
        }

};
