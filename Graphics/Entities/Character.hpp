#include "../../Libraries/RayLib/include/raylib.h"
#include "../Entity.hpp"
#include "../Core/Config.hpp"

#include <string>

class Character : public Entity {

    public:
        float walk_speed;
        float sprint_speed;
        int FrameRate;

        Character(void){}

        Character(std::string n, int eid, Vector2 eSize, std::vector<Collisions::Border> *clbp, Config* config)
        {
            name = n;
            id = eid;
            size = eSize;
            tid = -1;
            ec = Collisions::EntityCollision((Rectangle){pos.x, pos.y, size.x, size.y});
            bv = clbp;
            this->SetFromConfig(config);
        }

        Character(std::string n, int eid, Vector2 eSize, TextureList *tlp, const char* path, std::vector<Collisions::Border>* clbp, Config* config)
        {
            name = n;
            id = eid;
            size = eSize;
            AttachTextureList(tlp);
            AttachTexture(path);
            ec = Collisions::EntityCollision((Rectangle){pos.x, pos.y, size.x, size.y});
            bv = clbp;
            this->SetFromConfig(config);
        }

        void SetFromConfig(Config *config)
        {
            walk_speed = std::stof(config->GetValue("CHARACTER_SPEED"));
            sprint_speed = std::stof(config->GetValue("CHARACTER_SPRINT_SPEED"));
            FrameRate = std::stoi(config->GetValue("FRAME_RATE"));
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
                    pos.y -= this->sprint_speed / this->FrameRate;
                    sprint = 1;
                }
                if(IsKeyDown(KEY_A))
                {
                    pos.x -= this->sprint_speed / this->FrameRate;
                    sprint = 1;
                }
                if(IsKeyDown(KEY_S))
                {
                    pos.y += this->sprint_speed / this->FrameRate;
                    sprint = 1;
                }
                if(IsKeyDown(KEY_D))
                {
                    pos.x += this->sprint_speed / this->FrameRate;
                    sprint = 1;
                }
            }
            if(IsKeyDown(KEY_W))
            {
                pos.y -= this->walk_speed / this->FrameRate;
                walk = 1;
            }
            if(IsKeyDown(KEY_A))
            {
                pos.x -= this->walk_speed / this->FrameRate;
                walk = 1;
                direction = true;
            }
            if(IsKeyDown(KEY_S))
            {
                pos.y += this->walk_speed / this->FrameRate;
                walk = 1;
            }
            if(IsKeyDown(KEY_D))
            {
                pos.x += this->walk_speed / this->FrameRate;
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
