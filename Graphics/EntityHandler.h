#pragma once
#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Core/TextureLoader.h"
#include "Sprite.h"
#include "Entity.h"
#include "Collisions.h"

#include <stdio.h>

int createEntity(CollisionMaster *cm, EntityArray* ea, const char* name, int tid, Vector2 pos, Vector2 size);
EntityArray loadEntitiesFromFile(CollisionMaster *cm, TextureList* tl, const char* entities_path_list);
void renderEntities(TextureList* tl, EntityArray* ea);
void clearSelected(EntityArray* ea);
void updateEntities(EntityArray* ea);

int createEntity(CollisionMaster *cm, EntityArray* ea, const char* name, int tid, Vector2 pos, Vector2 size)
{
    int eid = genEntity(ea, name, tid, pos, size);
    addEntityCollision(cm, eid, size);
    return eid;
}

EntityArray loadEntitiesFromFile(CollisionMaster *cm, TextureList* tl, const char* entities_path_list)
{
    EntityArray ea = initEntityArray();
    FILE *fp = fopen(entities_path_list, "r");
    if(!fp)
    {
        printf("ERROR: Couldnt open entity list file [%s]\n", entities_path_list);
    } else {
        printf("INFO: Opened Entities List File [%s]\n", entities_path_list);

        int selector;
        char selector_png[64];
        Vector2 selector_size;
        float animSpeed;
        int animLen;

        if(fscanf(fp, "%d%s%f%f%f%d", &selector, selector_png, &selector_size.x, &selector_size.y, &animSpeed, &animLen) == 6 && selector == 1)
        {
            printf("INFO: Creating Entity Selector from [%s]\n", selector_png);
            ea.es = initEntitySelector(selector_size, tl, selector_png, animLen, animSpeed);
        }


        char name[32];
        char init_file_path[100];
        Vector2 size;
        while(fscanf(fp, "%s%s%f%f", name, init_file_path, &size.x, &size.y) == 4){
            char texture_path[100];
            char assets_file_path[100];
            Vector2 pos;
            FILE *fp1 = fopen(init_file_path, "r");
            if(!fp1)
            {
                printf("ERROR: Couldnt open entity initialization file [%s]\n", init_file_path);
            } else {
                if(fscanf(fp1, "%s%s%f%f", texture_path, assets_file_path, &pos.x, &pos.y) == 4)
                {
                    int tid = LoadTextureTL(tl, texture_path);
                    int eid = createEntity(cm, &ea, name, tid, pos, size);
                    Entity* e = getEntityP(&ea, eid);
                    loadAnimationsFromAssetFile(&e->ap, tl, tid, assets_file_path);
                } else {
                    printf("ERROR: Couldn't read contents of file [%s]\n", init_file_path);
                }
            }
        }
    }
    return ea;
}

void renderEntities(TextureList* tl, EntityArray* ea)
{
    for(int i = 0; i < ea->size; i++)
    {
        renderEntity(&ea->earray[i], &ea->es ,tl);
    }
}

void clearSelected(EntityArray* ea)
{
    for(int i = 0; i < ea->size; i++)
    {
        ea->earray[i].selected = false;
    }
}

void updateEntities(EntityArray* ea)
{
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        int index = 0;
        float dist_max = getMouseDistFromCenterRec(ea->earray[0].pos, ea->earray[0].size);
        clearSelected(ea);
        for(int i = 0; i < ea->size; i++)
        {
            if(checkEntityMouseClick(&ea->earray[i]))
            {
                float dist = getMouseDistFromCenterRec(ea->earray[i].pos, ea->earray[i].size);
                if(dist < dist_max)
                {
                    index = i;
                    dist_max = dist;
                }
            }
        }
        if(checkEntityMouseClick(&ea->earray[index]))
        {
            ea->earray[index].selected = true;
        }
    }
}

#endif
