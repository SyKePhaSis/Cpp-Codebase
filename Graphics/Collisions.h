#pragma once
#ifndef COLISSIONS_H
#define COLISSIONS_H

//INCLUDES
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#include "Core/Definitions.h"
#include "Entity.h"

//STRUCTS

typedef struct
{
    int capacity;
    int size;
    Rectangle* barray;
} BorderList;

typedef struct
{
    int sid;
    Vector2 size;
} EntityCollision;

typedef struct
{
    EntityCollision* earray;
    int size;
    int capacity;
} EntityCollisionList;

typedef struct
{
    EntityCollisionList ecl;
    BorderList bl;
} CollisionMaster;

//FUNCTION DECLARATIONS

//CollisionMaster
CollisionMaster initCollision();

//BorderList
void addBorder(CollisionMaster* cm, Rectangle r);
void loadBordersFromFile(CollisionMaster* cm, const char* border_file);

//EnityCollision
void addEntityCollision(CollisionMaster *cm, int sid, Vector2 size);
bool checkEntityMouseClick(Entity* e);

//CheckCollisionFunctions
void checkCollision(CollisionMaster* cm, EntityArray* ea_p);

//DrawCollisionRectangles
void drawBorders(CollisionMaster* cm);
void drawAllCollisionObjects(CollisionMaster* cm, EntityArray* ea_p);

//Helper
bool rectInScopeY(Rectangle object, Rectangle Entity, float padding);
bool rectInScopeX(Rectangle object, Rectangle Entity, float padding);
EntityCollision* GetEntityCollisionP(CollisionMaster *cm, int eid);
float getMouseDistFromCenterRec(Vector2 pos, Vector2 size);

//FUNCTIONS

//CollisionMaster
CollisionMaster initCollision()
{
    //Init Collision
    CollisionMaster cm;
    BorderList bl;
    EntityCollisionList ecl;

    //Init BorderList
    bl.capacity = BORDER_LIST_CAPACITY;
    bl.size = 0;
    bl.barray = malloc(bl.capacity * sizeof(Rectangle));

    //Init EnityCollisionList
    ecl.capacity = CHARACTER_COLL_LIST_CAPACITY;
    ecl.size = 0;
    ecl.earray = malloc(ecl.capacity * sizeof(EntityCollision));

    cm.ecl = ecl;
    cm.bl = bl;
    return cm;
}

//CollisionCHecks
void checkCollision(CollisionMaster* cm, EntityArray* ea_p)
{
    for(int i = 0; i < cm->ecl.size; i++)
    {
        Entity *ep = getEntityP(ea_p, cm->ecl.earray[i].sid);
        for(int j = 0; j < cm->bl.size; j++)
        {
            Vector2 c1  = (Vector2){ep->pos.x + cm->ecl.earray[i].size.x/2, ep->pos.y + cm->ecl.earray[i].size.y/2};
            Vector2 c2  = (Vector2){cm->bl.barray[j].x + cm->bl.barray[j].width/2, cm->bl.barray[j].y + cm->bl.barray[j].height/2};
            float dx = c1.x - c2.x;
            float dy = c1.y - c2.y;
            Rectangle entityRect = (Rectangle)
            {
                ep->pos.x,
                ep->pos.y,
                cm->ecl.earray[i].size.x,
                cm->ecl.earray[i].size.y
            };
            if(CheckCollisionRecs(cm->bl.barray[j], entityRect))
            {
                if(rectInScopeY(cm->bl.barray[j], entityRect, PADDING))
                {
                    if(dx > 0){
                       //COLLISION FROM RIGHT OF THE STATIC OBJECT
                       ep->pos.x = cm->bl.barray[j].x + cm->bl.barray[j].width;
                    }
                    if(dx < 0){
                       //COLLISION FROM LEFT OF THE STATIC OBJECT
                       ep->pos.x = cm->bl.barray[j].x - cm->ecl.earray[i].size.x;
                    }
                }
                else if(rectInScopeX(cm->bl.barray[j], entityRect, PADDING))
                {
                    if(dy > 0){
                        //COLLISION FROM DOWN OF THE STATIC OBJECT
                        ep->pos.y = cm->bl.barray[j].y + cm->bl.barray[j].height;
                    }
                    if(dy < 0){
                        //COLLISION FROM UP OF THE STATIC OBJECT
                        ep->pos.y = cm->bl.barray[j].y - cm->ecl.earray[i].size.y;
                    }
                }
            } else {
                continue;
            }
        }
    }
}

bool checkEntityMouseClick(Entity* e)
{
    Vector2 mpos = GetMousePosition();
    Rectangle rect = (Rectangle){
        e->pos.x,
        e->pos.y,
        e->size.x,
        e->size.y
    };
    if(CheckCollisionPointRec(mpos, rect))
    {
        return true;
    }
    return false;
}


//Border Functions
void drawBorders(CollisionMaster* cm)
{
    for(int i = 0; i < cm->bl.size; i++)
    {
        DrawRectangleLinesEx(cm->bl.barray[i], 1.0f, RAYWHITE);
    }
}

void addBorder(CollisionMaster* cm, Rectangle r)
{
    if(cm->bl.size == cm->bl.capacity)
    {
        printf("ERROR: Couldn't add Border because List was Full\n");
    } else {
        cm->bl.barray[cm->bl.size++] = r;
        printf("INFO: Successfully Added Border\n");
    }
}

void loadBordersFromFile(CollisionMaster* cm, const char* border_file)
{
    FILE *fp = fopen(border_file, "r");
    if(!fp)
    {
        printf("ERROR: Couldn't open Border Asset File\n");
    } else {
        Rectangle r;
        Vector2 v;
        while(fscanf(fp,"%f%f%f%f", &r.x, &r.y, &v.x, &v.y) == 4)
        {
            r.width = abs(r.x - v.x);
            r.height = abs(r.y - v.y);
            addBorder(cm,r);
        }
        fclose(fp);
        printf("INFO: Added Borders from [%s]\n", border_file);
    }
}

//EntityFunctions
void addEntityCollision(CollisionMaster *cm, int sid, Vector2 size)
{
    EntityCollision ec;
    if(cm->ecl.size == cm->ecl.capacity)
    {
        printf("ERROR: Couldn't add EntityCollisionObject because EnityCollisionList was full\n");
    } else {
        ec.sid = sid;
        ec.size = size;
        cm->ecl.earray[cm->ecl.size++] = ec;
        printf("INFO: Successfully added EntityCollisionObject to EnityCollisionList\n");
    }
}

//DrawAllCollisionShapes
void drawAllCollisionObjects(CollisionMaster* cm, EntityArray* ea_p)
{
    drawBorders(cm);
    for (int i = 0; i < cm->ecl.size; i++)
    {
        Entity *ep = getEntityP(ea_p, cm->ecl.earray[i].sid);
        Rectangle r = (Rectangle){
            ep->pos.x,
            ep->pos.y,
            cm->ecl.earray[i].size.x,
            cm->ecl.earray[i].size.y
        };
        DrawRectangleLinesEx(r, 1.0f, WHITE);
    }
}

//Helper
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

EntityCollision* GetEntityCollisionP(CollisionMaster *cm, int eid)
{
    for(int i = 0; i < cm->ecl.size; i++)
    {
        if(cm->ecl.earray[i].sid == eid)
        {
            return &cm->ecl.earray[i];
        }
    }
    return NULL;
}

float getMouseDistFromCenterRec(Vector2 pos, Vector2 size)
{
    Vector2 center;
    Vector2 MPos = GetMousePosition();
    center.x = pos.x + size.x/2;
    center.y = pos.y + size.y/2;
    float dx = center.x - MPos.x;
    float dy = center.y - MPos.y;
    float dist = pow(dy,2) + pow(dx,2);
    return sqrt(dist);
}


#endif
