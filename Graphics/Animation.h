#ifndef ANIMATION_H
#define ANIMATION_H

#define TEXTURE_ARRAY_SIZE 4

//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include "../Libraries/RayLib/include/raylib.h"

//STRUCTS
typedef struct
{
    int index;
    int size;
    int animIndex;
    float animSpeed[TEXTURE_ARRAY_SIZE];
    int animLen[TEXTURE_ARRAY_SIZE];
    int animfCounter;
    Texture2D tarray[TEXTURE_ARRAY_SIZE];
} AnimationProfile;

//FUNCTION DECLARATIONS
AnimationProfile initAP();
void addAnimationAP(AnimationProfile* ap, Texture2D t, float animSpeed, int animLen);
void loadAnimationsFromAssetFile(AnimationProfile* ap, const char* asset_file_path);

// ANIMATIONS
Rectangle getAnimTextPos(AnimationProfile* ap, int index, Vector2 size);

//FUNCTION IMPLEMENTATIONS

AnimationProfile initAP()
{
    AnimationProfile ap;
    ap.index = 0;
    ap.animIndex = 0;
    ap.size = 0;
    ap.animfCounter = 0;
    return ap;
}

void addAnimationAP(AnimationProfile* ap, Texture2D t, float animSpeed, int animLen)
{
    if(ap->size < TEXTURE_ARRAY_SIZE)
    {
        ap->tarray[ap->size] = t;
        ap->animSpeed[ap->size] = animSpeed;
        ap->animLen[ap->size] = animLen;
        ap->size++;
        printf("INFO: Added Image to AnimationProfile \n");
    }
    else
    {
        printf("ERROR: Couldn't add Texture Because List was full.\n");
        exit(0);
    }
}

void loadAnimationsFromAssetFile(AnimationProfile* ap, const char* asset_file_path)
{
    FILE* fp = fopen(asset_file_path,"r");
    if(!fp)
    {
        printf("ERROR: Couldn't Load Asset Files\n");
    }
    else
    {
        printf("INFO: Successfully opened asset file [%s]\n", asset_file_path);
        char path[100];
        float animSpeed;
        int animLen;
        Texture2D t;
        while(fscanf(fp,"%s%f%d", path, &animSpeed, &animLen) == 3)
        {
            t = LoadTexture(path);
            addAnimationAP(ap,t,animSpeed,animLen);
            printf("INFO: Loaded Animation from '%s'\n", path);
        }
        fclose(fp);
    }
}


Rectangle getAnimTextPos(AnimationProfile* ap, int index, Vector2 size)
{
    Rectangle rect;
    if(ap->index == index && ap->animfCounter >= (60/ap->animSpeed[ap->index]))
    {
        ap->animfCounter = 0;
        if(ap->animIndex < ap->animLen[ap->index])
        {
            ap->animIndex++;
        }
        else
        {
            ap->animIndex = 0;
        }
    } else {
        ap->animfCounter++;
        ap->index = index;
    }
    rect = (Rectangle){
        ap->animIndex * size.x, // Vector2 x top left corner of sprite
        0.0f,                 // Vector2 y top left corner of sprite
        1.0f * size.x,          // Vector2 x size (width)
        1.0f * size.y,          // Vector2 y size (height)
    };
    // printf("Counter = %d\n", ap->animfCounter);
    // printf("ap->index = %d\n", ap->index);
    // printf("ap->animIndex = %d\n", ap->animIndex);
    // printf("ap->animLen[ap->index] = %d\n", ap->animLen[ap->index]);
    // printf("ap->animSpeed[ap->index] = %d\n", ap->animSpeed[ap->index]);
    return rect;
}

#endif
