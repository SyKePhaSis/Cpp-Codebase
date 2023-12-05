#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>
#include "Core/Animation.h"

#define ENTITY_ARRAY_CAP 4

typedef struct {
    const char* name;
    int id;
    Vector2 pos;
    Vector2 size;
    int tid; // TextureId
    AnimationProfile ap;
} Entity;

typedef struct {
    int size;
    int cint;
    int capacity;
    Entity* earray;
} EntityArray;

//Function Declarations
EntityArray initEntityArray();
int genEntity(EntityArray* ea, const char* name, int tid, Vector2 pos, Vector2 size);
Entity* getEntityP(EntityArray* ea, int eid);
void updateEntityTexture(EntityArray* ea, int eid, TextureList* tl ,Texture2D t);
void deleteEntity(EntityArray* ea, int eid);
void setEntityPos(EntityArray* ea, int eid, Vector2 pos);

EntityArray initEntityArray()
{
    EntityArray ea;
    ea.size = 0;
    ea.capacity = ENTITY_ARRAY_CAP;
    ea.cint = 0;
    ea.earray = malloc(ea.capacity  * sizeof(Entity));
    return ea;
}

int genEntity(EntityArray* ea, const char* name, int tid, Vector2 pos, Vector2 size)
{
    AnimationProfile ap = initAP();
    Entity e;

    e.tid = tid;
    e.ap = ap;
    e.pos = pos;
    e.name = name;
    e.size = size;

    if(ea->size == ea->capacity)
    {
        Entity* tmp = ea->earray;
        ea->earray = realloc(ea->earray, ea->capacity++ * sizeof(Entity));
        if(!ea->earray)
        {
            printf("ERROR: Couldn't extend the Entity Array[MEMMORY_ERROR]\n");
            ea->earray = tmp;
            return -1;
        }
    }
    e.id = ea->cint;
    ea->cint++;
    ea->earray[ea->size++] = e;
    return e.id;
}

Entity* getEntityP(EntityArray* ea, int eid)
{
    for(int i = 0; i < ea->size; i++)
    {
        if(ea->earray[i].id == eid)
        {
            return  &ea->earray[i];
        }
    }
    return NULL;
}

void updateEntityTexture(EntityArray* ea, int eid, TextureList* tl ,Texture2D t)
{
    Entity* e = getEntityP(ea, eid);
    setTextureFromIdTL(tl, e->tid,t);
}

void deleteEntity(EntityArray* ea, int eid)
{
    for(int i = eid; i < ea->size; i++)
    {
        ea->earray[i] = ea->earray[i + 1];
    }
    ea->size--;
}

void setEntityPos(EntityArray* ea, int eid, Vector2 pos)
{
    Entity* e = getEntityP(ea, eid);
    e->pos = pos;
}

void setEntityIndex(EntityArray* ea, int eid, int index)
{
    Entity* e = getEntityP(ea, eid);
    if(e->ap.index != index){
        e->ap.index = index;
        e->ap.animfCounter = 0;
        e->ap.animIndex = 0;
    }
}

void renderEntity(Entity* e, TextureList* tl)
{
    Rectangle source = getAnimTextPosAP(&e->ap);
    source.width = source.width * e->size.x;
    source.height = source.height * e->size.y;
    source.x = source.x * e->size.x;
    Texture2D t = getTextureFromIdTL(tl,e->ap.tarray[e->ap.index]);
    DrawTextureRec(t, source, (Vector2){e->pos.x, e->pos.y}, WHITE);
}

#endif
