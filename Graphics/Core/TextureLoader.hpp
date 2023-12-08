#pragma once
#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include "../../Libraries/RayLib/include/raylib.h"

#include <cstdio>
#include <cstdlib>
#include <stdbool.h>
#include <string.h>

#include "Definitions.hpp"

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

class TextureList {

    public:
        int tid;
        int size;
        int capacity;
        TextureItem* tiarray;

        //TextureList

        TextureList(){

            //Texture List Parameters
            tid = 0;
            size = 0;
            capacity = TEXTURE_LIST_CAPACITY;
            tiarray = (TextureItem*)malloc(capacity * sizeof(TextureItem));

            //Slots List
            sl.size = 0;
            sl.capacity = TEXTURE_LIST_CAPACITY;
            sl.slots = (int* )malloc(sl.capacity * sizeof(TextureItem));
            clearSlotsList();
        }

        int LoadTextureToList(const char* path)
        {
            int id = getIdFromPath(path);
            if(id == -1)
            {
                int index = getIndexFromSlots();
                if(index == -1 && size == capacity)
                {
                    expandTextureList();
                    index = size;
                } else if(index == -1)
                {
                    index = size;
                }
                TextureItem ti;
                ti.id = tid;
                strcpy(ti.path,path);
                ti.text = LoadTexture(path);
                tiarray[index] = ti;
                tid++;
                size++;
                printf("INFO: Loaded Texture [%s] to [TextureArray]\n",path);
                return ti.id;
            } else {
                reduceSlotsList();
            }
            return id;
        }

        void unloadTexture(int id)
        {
            int index = getIndexFromId(id);
            if(index != -1)
            {
                AddSlot(index);
            } else {
                printf("ERROR: Couldn't find Texture through ID [%d]", id);
            }
        }

        Texture2D getTextureFromId(int id)
        {
            int index = getIndexFromId(id);
            if(index != -1)
            {
                return tiarray[index].text;
            }
            exit(-1);
        }

        ~TextureList()
        {
            free(tiarray);
            free(sl.slots);
        }

    private:
        SlotsList sl;

        void AddSlot(int index)
        {
            if(sl.size == sl.capacity)
            {
                expandSlotsList();
            }
            sl.slots[sl.size] = index;
            sl.size++;
        }


        void reduceSlotsList()
        {
            for(int i = sl.size; i > 0; i--)
            {
                if(sl.slots[i - 1] == -1)
                {
                    sl.slots[i - 1] = sl.slots[i];
                    sl.size--;
                }
            }
        }

        void clearSlotsList(void)
        {
            for(int i = 0; i < sl.capacity; i++)
            {
                sl.slots[i] = -1;
            }
        }

        int getIndexFromSlots(void)
        {
            for(int i = 0; i < sl.size; i++)
            {
                if(sl.slots[i] != -1)
                {
                    return sl.slots[i];
                }
            }
            return -1;
        }

        int getIdFromPath(const char* path)
        {
            for(int i = 0; i < size; i++)
            {
                if(strcmp(tiarray[i].path, path) == 0){
                    return tiarray[i].id;
                }
            }
            return -1;
        }

        int getIndexFromId(int id)
        {
            for(int i = 0; i < size; i++)
            {
                if(tiarray[i].id == id)
                {
                    return i;
                }
            }
            return -1;
        }

        void expandTextureList(void)
        {
            capacity += 4;
            tiarray = (TextureItem* )realloc(tiarray, capacity * sizeof(TextureItem));
            if(tiarray)
            {
                printf("ERROR: Couldn't expand texture array\n");
                exit(-1);
            }
        }

        void expandSlotsList(void)
        {
            sl.capacity++;
            sl.slots  = (int*)realloc(sl.slots, sl.capacity * sizeof(int));
            if(!sl.slots)
            {
                printf("ERROR: Couldn't successfully extended slots array\n");
                exit(0);
            }
        }
};

#endif
