#pragma once
#ifndef COLISSIONS_H
#define COLISSIONS_H

//INCLUDES
#include <cmath>
#include <cstdio>
#include <cstdbool>
#include <fstream>
#include <vector>

#include "Definitions.hpp"

namespace Collisions
{

    bool rectInScopeY(Rectangle object, Rectangle Entity, float padding)
    {
        if(Entity.y + Entity.height > object.y + padding && Entity.y  < object.y + object.height - padding)
        {
            return true;
        } else {
            return false;
        }
    }

    bool rectInScopeX(Rectangle object, Rectangle Entity, float padding)
    {
        if(Entity.x + Entity.width - padding > object.x + padding && Entity.x < object.x + object.width - padding)
        {
            return true;
        } else {
            return false;
        }
    }

    class Border {
        public:
            Rectangle rect;

        Border(Rectangle border){
            rect = border;
        }

        void DrawBorder(void)
        {
            DrawRectangleLinesEx(rect, 1.0f ,WHITE);
        }
    };

    class EntityCollision {
        public:
            Rectangle rect;

            EntityCollision(void){}

            EntityCollision(Rectangle r)
            {
                rect = r;
            }

            EntityCollision(Vector2 sP, Vector2 eP)
            {
                rect = (Rectangle){sP.x, sP.y, std::abs(eP.x - sP.x), std::abs(eP.y - sP.y)};
            }

            void CheckCollision(Rectangle r, Vector2* Epos)
            {
                Vector2 c1  = (Vector2){r.x + r.width/2, r.y + r.height/2};
                Vector2 c = (Vector2){rect.x + rect.width/2, rect.y + rect.height/2};
                float dx = c.x - c1.x;
                float dy = c.y - c1.y;
                if(CheckCollisionRecs(r, rect))
                {
                    if(Collisions::rectInScopeY(r, rect, PADDING))
                    {
                        if(dx > 0){
                            //COLLISION FROM RIGHT OF THE STATIC OBJECT
                            Epos->x = r.x + r.width;
                        }
                        if(dx < 0){
                            //COLLISION FROM LEFT OF THE STATIC OBJECT
                            Epos->x = r.x - rect.width;
                        }
                    }
                    else if(Collisions::rectInScopeX(r, rect, PADDING))
                    {
                        if(dy > 0){
                            //COLLISION FROM DOWN OF THE STATIC OBJECT
                            Epos->y = r.y + r.height;
                        }
                        if(dy < 0){
                            //COLLISION FROM UP OF THE STATIC OBJECT
                            Epos->y = r.y - rect.height;
                        }
                    }
                }
            }

            void DrawBorder(void)
            {
                DrawRectangleLinesEx(rect, 1.0f ,WHITE);
            }

            bool checkEntityMouseClick(void)
            {
                Vector2 mpos = GetMousePosition();
                if(CheckCollisionPointRec(mpos, rect))
                {
                    return true;
                }
                return false;
            }

    };

    class Master {
        public:
            std::vector<Border> bv;

            Master(void)
            {}

            void LoadBordersFromFile(const char* border_file)
            {
                std::fstream dfile(border_file);
                if(!dfile)
                {
                    printf("ERROR: Couldn't open Border Asset File\n");
                } else {
                    Rectangle r = (Rectangle){0.0f,0.0f,0.0f,0.0f};
                    Vector2 v = (Vector2){0.0f, 0.0f};
                    while(dfile >> r.x >> r.y >> v.x >> v.y)
                    {
                        r.width = abs(r.x - v.x);
                        r.height = abs(r.y - v.y);
                        Collisions::Border border(r);
                        bv.push_back(border);
                        printf("INFO: Added Border from [%s]\n", border_file);
                    }
                }
                dfile.close();
            }

            void DrawBorders(void)
            {
                for(auto& border: bv)
                {
                    border.DrawBorder();
                }
            }

    };


};

#endif
