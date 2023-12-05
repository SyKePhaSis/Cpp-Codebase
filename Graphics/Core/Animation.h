#ifndef ANIMATION_H
#define ANIMATION_H

//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include "../../Libraries/RayLib/include/raylib.h"
#include "Definitions.h"

//STRUCTS
typedef struct
{
    int index;
    int size;
    int animIndex;
    float animSpeed[TEXTURE_ARRAY_SIZE];
    int animLen[TEXTURE_ARRAY_SIZE];
    int animfCounter;
    int tarray[TEXTURE_ARRAY_SIZE];
} AnimationProfile;

typedef struct
{
    int size;
    int animIndex;
    float animSpeed;
    int animLen;
    int animfCounter;
    Texture2D sprite;
} ObjectAnimation;


AnimationProfile initAP();
ObjectAnimation initOA();


void addAnimationAP(AnimationProfile* ap, int tid, float animSpeed, int animLen);
void loadAnimationsFromAssetFile(AnimationProfile* ap, TextureList* tl, int tid,const char* asset_file_path);

void addAnimationOA(ObjectAnimation* oa, float animSpeed, int animLen, Texture2D t);

Rectangle getAnimTextPosAP(AnimationProfile* ap);
Rectangle getAnimTextPosOA(ObjectAnimation* oa);

//animationProfile
AnimationProfile initAP()
{
    AnimationProfile ap;
    ap.index = 0;
    ap.animIndex = 0;
    ap.size = 0;
    ap.animfCounter = 0;
    return ap;
}

//Object Animation
ObjectAnimation initOA(){
    ObjectAnimation oa;
    oa.animIndex = 0;
    oa.animSpeed = 1.0f;
    oa.animLen = 1;
    oa.animfCounter = 0;
    return oa;
}

void addAnimationAP(AnimationProfile* ap, int tid, float animSpeed, int animLen)
{
    if(ap->size < TEXTURE_ARRAY_SIZE)
    {
        ap->tarray[ap->size] = tid;
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

void loadAnimationsFromAssetFile(AnimationProfile* ap, TextureList* tl, int tid, const char* asset_file_path)
{
    FILE* fp = fopen(asset_file_path,"r");
    if(!fp)
    {
        printf("ERROR: Couldn't Load Asset Files\n");
    }
    else
    {
        printf("INFO: Successfully opened asset file [%s]\n", asset_file_path);
        char path[64];
        float animSpeed;
        int animLen;
        int tid;
        while(fscanf(fp,"%s%f%d", path, &animSpeed, &animLen) == 3)
        {
            tid = LoadTextureTL(tl,path);
            addAnimationAP(ap,tid,animSpeed,animLen);
            printf("INFO: Loaded Animation from '%s' with TextureId [%d]\n", path, tid);
        }
        fclose(fp);
    }
}

Rectangle getAnimTextPosOA(ObjectAnimation* oa)
{
    Rectangle rect;
    if(oa->animfCounter >= (FRAME_RATE/oa->animSpeed))
    {
        oa->animfCounter = 0;
        if(oa->animIndex < oa->animLen)
        {
            oa->animIndex++;
        }
        else
        {
            oa->animIndex = 0;
        }
    } else {
        oa->animfCounter++;
    }
    rect = (Rectangle){
        oa->animIndex,
        0.0f,
        1.0f,
        1.0f
    };
    return rect;
}

Rectangle getAnimTextPosAP(AnimationProfile* ap)
{
    Rectangle rect;
    if(ap->animfCounter >= (FRAME_RATE/ap->animSpeed[ap->index]))
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
    }
    rect = (Rectangle){
        ap->animIndex, // Vector2 x top left corner of sprite
        0.0f,                 // Vector2 y top left corner of sprite
        1.0f,          // Vector2 x size (width)
        1.0f,          // Vector2 y size (height)
    };
    return rect;
}



void addAnimationOA(ObjectAnimation* oa, float animSpeed, int animLen, Texture2D t)
{
    oa->sprite = t;
    oa->animSpeed = animSpeed;
    oa->animLen = animLen;
    printf("INFO: Added Object Animation\n");
}

#endif
