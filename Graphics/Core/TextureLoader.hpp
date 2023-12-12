#pragma once
#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include "../../Libraries/RayLib/include/raylib.h"

#include <cstdio>
#include <cstdlib>
#include <stdbool.h>
#include <string.h>
#include <vector>

#include "Definitions.hpp"

class TextureList {

    typedef struct
    {
        int id;
        Texture2D text;
        char path[64];
    } TextureItem;

    public:
        int tid;
        int size;
        std::vector<TextureItem> tiarray;

        //TextureList

        TextureList(void)
        {
            //Texture List Parameters
            tid = 0;
            size = 0;
        }

        int LoadTextureToList(const char* path)
        {
            int id = getIdFromPath(path);
            if(id == -1)
            {
                TextureItem ti;
                ti.id = tid;
                strcpy(ti.path,path);
                ti.text = LoadTexture(path);
                tiarray.push_back(ti);
                tid++;
                size++;
                printf("INFO: Loaded Texture [%s] to [TextureArray]\n",path);
                return ti.id;
            }
            return id;
        }

        void unloadTexture(int id)
        {
            int index = getIndexFromId(id);
            if(index != -1)
            {
                tiarray.erase(tiarray.begin() + index );
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
            tiarray.clear();
        }

    private:

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

};

#endif
