#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H


#include "../../Libraries/RayLib/include/raylib.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "Definitions.h"

typedef struct
{
    int id;
    Texture2D text;
    char path[64];
} TextureItem;

typedef struct
{
    int size;
    int capacity;
    int* slots;
} SlotsList;

typedef struct
{
    int size;
    int capacity;
    SlotsList sl;
    TextureItem* array;
} TextureList;

TextureList initTextureList(void);
int loadTextureTL(TextureList *tl, const char* path);
int getIdFromPathTL(TextureList *tl, const char* path);
void addSlotSL(TextureList *tl, int index);
int getIndexSL(TextureList *tl,int index);
void removeSlotSL(TextureList *tl, int index);
void unloadTextureTL(TextureList *tl, int id);
void freeTextureList(TextureList *tl);


TextureList initTextureList(void)
{
    //Initializing texture list
    TextureList tl;
    tl.size = 0;
    tl.capacity = TEXTURE_LIST_CAPACITY;
    tl.array = malloc(tl.capacity * sizeof(TextureItem));

    //Initializing slot list
    SlotsList sl;
    sl.size = 0;
    sl.capacity = TEXTURE_LIST_CAPACITY;
    sl.slots = malloc(sl.capacity * sizeof(int));
    for(int i =0; i < sl.size; i++)
    {
        sl.slots[i] = -1;
    }
    tl.sl = sl;
    return tl;
}

int LoadTextureTL(TextureList *tl, const char* path)
{
    int id = getIdFromPathTL(tl,path);
    if(id == -1){
        int index = -1;
        for(int i = 0; i < tl->sl.size; i++)
        {
            if(tl->sl.slots[i] != -1)
            {
                index = i;
            }
        }
        if(index == -1)
        {
            index = tl->size;
        }
        if(index == tl->capacity)
        {
            tl->capacity += 4;
            tl->array = realloc(tl->array, tl->capacity * sizeof(TextureItem));
            if(!tl->array)
            {
                printf("ERROR: Couldn't expand texture array\n");
                return -1;
            }
        }
        TextureItem ti;
        ti.id = index;
        strcpy(ti.path,path);
        ti.text = LoadTexture(path);
        tl->array[tl->size] = ti;
        tl->size++;
        printf("INFO: Loaded Texture [%s] to [TextureArray]\n",path);
        return ti.id;
    }
    return id;
}

int getIdFromPathTL(TextureList *tl, const char* path)
{
    for(int i = 0; i < tl->size; i++)
    {
        if(tl->array[i].path == path)
        {
            return tl->array[i].id;
        }
    }
    return -1;
}

Texture2D getTextureFromIdTL(TextureList* tl, int id)
{
    for(int i = 0; i < tl->size; i++)
    {
        if(tl->array[i].id == id)
        {
            return tl->array[i].text;
        }
    }
    exit(0);
}

void setTextureFromIdTL(TextureList* tl, int id, Texture t)
{
    for(int i = 0; i < tl->size; i++)
    {
        if(tl->array[i].id == id)
        {
            tl->array[i].text = t;
        }
    }
}

void addSlotSL(TextureList *tl, int index)
{
    if(tl->sl.size == tl->sl.capacity)
    {
        tl->sl.capacity++;
        tl->sl.slots  = realloc(tl->sl.slots, tl->sl.capacity * sizeof(int));
        if(!tl->sl.slots)
        {
            printf("ERROR: Couldn't successfully extended slots array\n");
            exit(0);
        }

    }
    tl->sl.slots[tl->sl.size] = index;
    tl->sl.size++;
}

int getIndexSL(TextureList *tl,int index)
{
    for(int i = 0; i < tl->sl.size; i++)
    {
        if(i == index)
        {
            return i;
        }
    }
    return -1;
}

void removeSlotSL(TextureList *tl, int index)
{
    int slindex = getIndexSL(tl, index);
    for(int i = slindex; i < tl->sl.size; i++)
    {
        tl->sl.slots[i] = tl->sl.slots[i + 1];
    }
    tl->sl.size--;
}

void unloadTextureTL(TextureList *tl, int id)
{
    for(int i = 0; i < tl->size; i++)
    {
        if(tl->array[i].id == id)
        {
            addSlotSL(tl,i);
        }
    }
}

void freeTextureList(TextureList *tl)
{
    free(tl->sl.slots);
    free(tl->array);
}

#endif
