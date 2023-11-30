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
    Texture2D tarray[TEXTURE_ARRAY_SIZE];
} AnimationProfile;

//FUNCTION DECLARATIONS
AnimationProfile initAP();
void addTextureAP(AnimationProfile* ap, Texture2D t);

//FUNCTION IMPLEMENTATIONS

AnimationProfile initAP()
{
    AnimationProfile ap;
    ap.index = 0;
    ap.size = 0;
    return ap;
}

void addTextureAP(AnimationProfile* ap, Texture2D t)
{
    if(ap->size < 4)
    {
        ap->tarray[ap->size] = t;
        ap->size++;
        printf("[INFO] Added Image to AnimationProfile");
    }
    else
    {
        printf("[ERROR] Couldn't add Texture Because List was full.");
        exit(0);
    }
}

#endif
