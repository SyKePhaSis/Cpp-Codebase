#pragma once
#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include "../../Libraries/RayLib/include/raylib.h"

#include <cstdio>
#include <cstdlib>
#include <cstdbool>
#include <string>
#include <cstring>
#include <vector>

#include "Definitions.hpp"

class TextureList {

    typedef struct
    {
        int id;
        Texture2D text;
        std::string path;
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

        int LoadTextureToList(const std::string path)
        {
            int id = getIdFromPath(path);
            if(id == -1)
            {
                TextureItem ti;
                ti.id = tid;
                ti.path = path;
                ti.text = LoadTexture(path.c_str());
                tiarray.push_back(ti);
                tid++;
                size++;
                printf("INFO: Loaded Texture [%s] to [TextureArray]\n",path.c_str());
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

        int getIdFromPath(const std::string path)
        {
            for(int i = 0; i < size; i++)
            {
                if(tiarray[i].path.compare(path) == 0){
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
