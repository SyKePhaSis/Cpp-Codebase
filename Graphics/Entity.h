#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>
#include <stdbool.h>
#include "Core/Animation.h"
#include "Core/TextureLoader.h"

#define ENTITY_ARRAY_CAP 4

typedef struct
{
    Vector2 size;
    ObjectAnimation oa;
} EntitySelector;

typedef struct {
    const char* name;
    int id;
    Vector2 pos;
    Vector2 size;
    int tid; // TextureId
    AnimationProfile ap;
    bool selected;
} Entity;

typedef struct {
    int size;
    int cint;
    int capacity;
    Entity* earray;
    EntitySelector es;
} EntityArray;




//Function Declarations
EntityArray initEntityArray();
EntitySelector initEntitySelector(Vector2 size, TextureList* tl,const char* path, int animLen, float animSpeed);
int genEntity(EntityArray* ea, const char* name, int tid, Vector2 pos, Vector2 size);
Entity* getEntityP(EntityArray* ea, int eid);
void updateEntityTexture(EntityArray* ea, int eid, TextureList* tl ,Texture2D t);
void deleteEntity(EntityArray* ea, int eid);
void setEntityPos(EntityArray* ea, int eid, Vector2 pos);
Entity* getSelectedEntityP(EntityArray* ea);

EntityArray initEntityArray()
{
    EntityArray ea;
    ea.size = 0;
    ea.capacity = ENTITY_ARRAY_CAP;
    ea.cint = 0;
    ea.earray = malloc(ea.capacity  * sizeof(Entity));
    return ea;
}

EntitySelector initEntitySelector(Vector2 size, TextureList* tl,const char* path, int animLen, float animSpeed)
{
    EntitySelector es;
    int id = LoadTextureTL(tl, path);
    es.size = size;
    addAnimationOA(&es.oa, animSpeed, animLen, id);
    return es;
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
    e.selected = false;

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

Entity* getSelectedEntityP(EntityArray* ea)
{
    for(int i = 0; i < ea->size; i++)
    {
        if(ea->earray[i].selected)
        {
            return &ea->earray[i];
        }
    }
    return NULL;
}

void renderEntity(Entity* e, EntitySelector *ea, TextureList* tl)
{
    Rectangle source = getAnimTextPosAP(&e->ap);
    source.width = source.width * e->size.x;
    source.height = source.height * e->size.y;
    source.x = source.x * e->size.x;
    Texture2D t = getTextureFromIdTL(tl,e->ap.tarray[e->ap.index]);
    DrawTextureRec(t, source, (Vector2){e->pos.x, e->pos.y}, WHITE);
    if(e->selected)
    {
        Rectangle select_source = getAnimTextPosOA(&ea->oa);
        select_source.width = select_source.width * ea->size.x;
        select_source.height = select_source.height * ea->size.y;
        select_source.x = select_source.x * ea->size.x;
        Vector2 sp; //Startinng point
        sp.x = e->pos.x - (ea->size.x - e->size.x)/2;
        sp.y = e->pos.y - (ea->size.y - e->size.y)/2;
        Texture2D t = getTextureFromIdTL(tl, ea->oa.spriteId);
        DrawTextureRec(t, select_source, sp, WHITE);
    }
}

#endif
