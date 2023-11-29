#ifndef SPRITES_H
#define SPRITES_H

#define SP_INIT_SIZE 4

//VARIABLES
int sid = 0;

// INCLUDES
#include "../Libraries/RayLib/include/raylib.h"
#include <stdlib.h>
#include <stdio.h>

//STRUCTS
typedef struct
{
    int id;
    Vector2 pos;
    Texture2D texture;
} Sprite;

typedef struct
{
    size_t capacity;
    size_t size;
    Sprite *array;
} SpriteList;

//FUNCTION DECLARATIONS

////INITIALIZATION AND FREEING
Sprite SpriteInit(Image img);
void InitSpriteList(SpriteList *sl_p);
void freeSpriteList(SpriteList *container);

////LIST FUNCTIONS
void insertItem(SpriteList* sl_p, Sprite sp);
void updateItem(SpriteList *list, int sid);
Sprite* getItemP(SpriteList *sl_p, int sid);
void deleteItem(SpriteList *sl_p, int sid);
void printArray(SpriteList *sl_p);

////RENDERING FUCNTIONS
void render(SpriteList *sl_p, int sid);
void renderSection(SpriteList *sl_p, int Ssid, int Esid);

////MODIFYING  SPRITES
void setVec(SpriteList *sl_p, Vector2 vec, int sid);

//DEBUGGIN
void printSpriteInfo(SpriteList *sl_p, int sid);

//FUNCTION
Sprite SpriteInit(Image img)
{
   Vector2 v = (Vector2){0.0f, 0.0f};
   Sprite s;
   s.texture = LoadTextureFromImage(img);
   s.pos = v;
   return s;
}

void InitSpriteList(SpriteList *sl_p)
{
    sl_p->size = 0;
    sl_p->capacity = SP_INIT_SIZE;
    sl_p->array = malloc(SP_INIT_SIZE * sizeof(Sprite*));
    if (!sl_p->array){
        printf("[ERROR]Memory Allocation Failed\n");
        exit(0);
    }
}

void insertItem(SpriteList* sl_p, Sprite sp)
{

    if(sl_p->size == sl_p->capacity)
    {
        Sprite *temp = sl_p->array;
        sl_p->capacity <<= 1;
        sl_p->array = realloc(sl_p->array, sl_p->capacity * sizeof(Sprite));
        if(!sl_p->array) {
            printf("[ERROR]Out of Memory\n");
            sl_p->array = temp;
        }
    }
    sp.id = sid;
    sid++;
    sl_p->array[sl_p->size++] = sp;
}

Sprite* getItemP(SpriteList *sl_p, int sid)
{
    return &sl_p->array[sid];
}

void updateItem(SpriteList *sl_p, int sid)
{
    if (sid >= sl_p->size) {
        printf("[ERROR]Index Out of Bounds\n");
    }
}

void deleteItem(SpriteList *sl_p, int sid)
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

void printArray(SpriteList *sl_p)
{
    printf("Sprite Id's :");
    for(int i = 0; i < sl_p->size; i++)
    {
        printf("%d ", sl_p->array[i].id);
    }
    printf("\nSize: ");
    printf("%llu", sl_p->size);
    printf("\nCapacity: ");
    printf("%llu\n", sl_p->capacity);
}

void renderSprite(SpriteList *sl_p, int sid)
{
    DrawTextureV(sl_p->array[sid].texture, sl_p->array[sid].pos, WHITE);
}

// IS INCLUSIVE
void renderSection(SpriteList *sl_p, int Ssid, int Esid)
{
    for(int i = Ssid; i < Esid; i++)
    {
        DrawTextureV(sl_p->array[i].texture, sl_p->array[i].pos, WHITE);
    }
}

void freeSpriteList(SpriteList* sl_p)
{
    free(sl_p->array);
    free(sl_p);
}

//CHANGE SPRITE LOCATION
void setVec(SpriteList *sl_p, Vector2 vec, int sid)
{
    sl_p->array[sid].pos = vec;
}

void printSpriteInfo(SpriteList *sl_p, int sid)
{
    Sprite sp = sl_p->array[sid];
    printf("[INFO] Sprite Info:\n");
    printf("[INFO] id: %d\n", sp.id);
    printf("[INFO] pos: ( %f , %f )\n", sp.pos.x, sp.pos.y);
}

#endif
