#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Sprite.h"
#include "Entity.h"
#include "Collisions.h"

#include <stdio.h>

int createEntity(CollisionMaster *cm, EntityArray* ea, const char* name, Texture2D t, Vector2 pos, Vector2 size)
{
    int eid = genEntity(ea, name, t, pos, size);
    addEntityCollision(cm, eid, size);
    return eid;
}

EntityArray loadEntitiesFromFile(CollisionMaster *cm, const char* entities_path_list)
{
    EntityArray ea = initEntityArray();
    FILE *fp = fopen(entities_path_list, "r");
    if(!fp)
    {
        printf("ERROR: Couldnt open entity list file [%s]\n", entities_path_list);
    } else {
        printf("INFO: Opened Entities List File [%s]\n", entities_path_list);
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
                    Texture2D t = LoadTexture(texture_path);
                    int eid = createEntity(cm, &ea, name, t, pos, size);
                    Entity* e = getEntityP(&ea, eid);
                    loadAnimationsFromAssetFile(&e->ap, assets_file_path);
                } else {
                    printf("ERROR: Couldn't read contents of file [%s]\n", init_file_path);
                }
            }
        }
    }
    return ea;
}

void renderEntities(EntityArray* ea)
{
    for(int i = 0; i < ea->size; i++)
    {
        renderEntity(&ea->earray[i]);
    }
}

#endif
