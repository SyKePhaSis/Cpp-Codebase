#pragma once
#ifndef SPRITES_H
#define SPRITES_H

//VARIABLES
int sid = 0;

// INCLUDES
#include "../Libraries/RayLib/include/raylib.h"
#include "Core/Animation.h"
#include "Core/Definitions.h"
#include "Core/TextureLoader.h"
#include <stdlib.h>
#include <stdio.h>

//STRUCTS
typedef struct
{
    int id;
    Vector2 pos;
    bool animated;
    Texture2D t;
    ObjectAnimation anim;
} ObjectSprite;

typedef struct
{
    size_t capacity;
    size_t size;
    ObjectSprite *array;
} ObjectSpriteList;

//FUNCTION DECLARATIONS

////INITIALIZATION AND FREEING
ObjectSprite ObjectSpriteInit(Image img, float idleAnimSpeed, int animSize);
void InitObjectSpriteList(ObjectSpriteList *sl_p);
void freeObjectSpriteList(ObjectSpriteList *container);

////LIST FUNCTIONS
int insertItem(ObjectSpriteList* sl_p, ObjectSprite sp);
void updateItem(ObjectSpriteList *list, int sid);
ObjectSprite* getItemP(ObjectSpriteList *sl_p, int sid);
void deleteItem(ObjectSpriteList *sl_p, int sid);
void printArray(ObjectSpriteList *sl_p);

////RENDERING FUCNTIONS
void render(ObjectSpriteList *sl_p, int sid);
void renderSection(ObjectSpriteList *sl_p, TextureList* tl, int Ssid, int Esid);
void renderAnim(ObjectSprite* sp, int index, Vector2 size, int animLength);
void renderObjectSprite(ObjectSpriteList *sl_p, TextureList* tl,int sid);

////MODIFYING  SPRITES
void setVec(ObjectSpriteList *sl_p, Vector2 vec, int sid);

//DEBUGGIN
void printObjectSpriteInfo(ObjectSpriteList *sl_p, int sid);

//FUNCTION
ObjectSprite ObjectSpriteInit(Image staticImg, float idleAnimSpeed, int animSize)
{
   Vector2 v = (Vector2){0.0f, 0.0f};
   ObjectSprite s;
   Texture t = LoadTextureFromImage(staticImg);
   s.pos = v;
   s.t = t;
   s.animated = false;
   return s;
}

void InitObjectSpriteList(ObjectSpriteList *sl_p)
{
    sl_p->size = 0;
    sl_p->capacity = SP_INIT_SIZE;
    sl_p->array = malloc(SP_INIT_SIZE * sizeof(ObjectSprite));
    if (!sl_p->array){
        printf("[ERROR]Memory Allocation Failed\n");
        exit(0);
    }
}

int insertItem(ObjectSpriteList* sl_p, ObjectSprite sp)
{

    if(sl_p->size == sl_p->capacity)
    {
        ObjectSprite *temp = sl_p->array;
        sl_p->capacity <<= 1;
        sl_p->array = realloc(sl_p->array, sl_p->capacity * sizeof(ObjectSprite));
        if(!sl_p->array) {
            printf("[ERROR]Out of Memory\n");
            sl_p->array = temp;
        }
    }
    sp.id = sid;
    sid++;
    sl_p->array[sl_p->size++] = sp;
    return sp.id;
}

ObjectSprite* getObjectSpriteP(ObjectSpriteList *sl_p, int sid)
{
    return &sl_p->array[sid];
}

void updateObjectSprite(ObjectSpriteList *sl_p, int sid)
{
    if (sid >= sl_p->size) {
        printf("[ERROR]Index Out of Bounds\n");
    }
}

void deleteObjectSprite(ObjectSpriteList *sl_p, int sid)
{
    if(sid >= sl_p->size) {
        printf("[ERROR]Index Out of Bounds\n");
        return;
    }

    for(int i = sid; i < sl_p->capacity; i++)
    {
        sl_p->array[i] = sl_p->array[i + 1];
        sl_p->array[i].id = i;
    }
    sid = sl_p->size;
    sl_p->size--;
}

void printArray(ObjectSpriteList *sl_p)
{
    printf("ObjectSprite Id's :");
    for(int i = 0; i < sl_p->size; i++)
    {
        printf("%d ", sl_p->array[i].id);
    }
    printf("\nSize: ");
    printf("%llu", sl_p->size);
    printf("\nCapacity: ");
    printf("%llu\n", sl_p->capacity);
}

void renderObjectSprite(ObjectSpriteList *sl_p, TextureList* tl,int sid)
{
    if(sl_p->array[sid].animated == true)
    {
        // GET ANIMATION RECTANGLE
        // int index = sl_p->array[sid].anim.index;
        Texture2D t = getTextureFromIdTL(tl, sl_p->array[sid].anim.spriteId);
        DrawTextureV(t, sl_p->array[sid].pos, WHITE);
    } else {
        DrawTextureV(sl_p->array[sid].t, sl_p->array[sid].pos, WHITE);
    }
}

// IS INCLUSIVE
void renderSection(ObjectSpriteList *sl_p, TextureList* tl, int Ssid, int Esid)
{
    for(int i = Ssid; i < Esid; i++)
    {
        if(sl_p->array[i].animated == true)
        {
            // GET ANIMATION RECTANGLE
            Texture2D t = getTextureFromIdTL(tl, sl_p->array[sid].anim.spriteId);
            DrawTextureV(t, sl_p->array[i].pos, WHITE);
        } else {
            DrawTextureV(sl_p->array[i].t, sl_p->array[i].pos, WHITE);
        }
    }
}

void freeObjectSpriteList(ObjectSpriteList *sl_p)
{
    free(sl_p->array);
    free(sl_p);
}

//CHANGE SPRITE LOCATION
void setVec(ObjectSpriteList *sl_p, Vector2 vec, int sid)
{
    sl_p->array[sid].pos = vec;
}

void printObjectSpriteInfo(ObjectSpriteList *sl_p, int sid)
{
    ObjectSprite sp = sl_p->array[sid];
    printf("[INFO] ObjectSprite Info:\n");
    printf("[INFO] id: %d\n", sp.id);
    printf("[INFO] pos: ( %f , %f )\n", sp.pos.x, sp.pos.y);
}

#endif
