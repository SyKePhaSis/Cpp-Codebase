#ifndef PPM_H
#define PPM_H

//INCLUDES
#include <stdio.h>
#include <stdbool.h>
#include "../Math/Power.h"

//STRUCTS
typedef struct
{
    int r;
    int b;
    int g;
} Color;

typedef struct
{
    int x;
    int y;
    Color c;
} Pixel;

typedef struct
{
    int x;
    int y;
} Point;

typedef struct
{
    FILE* fp;
    int width;
    int height;
    int maxSatVal;
} Image;


//FUNCTION DECLARATIONS
Image create(const char* name ,int width, int height, int maxSatVal);
void writePixel(FILE* fp, Color p);
void fill(Image Im, Color bg);
void drawCircle(Image Im,  Color fg, Color bg, int radius, bool center);

//FUNCTIONS
Image create(const char* name,int width, int height, int maxSatVal)
{
    FILE* fp;
    fp = fopen(name, "wb");
    if(!fp){
        printf("Couldn't create file!");
    } else {
        printf("File Created Successfully!");
    }
    fprintf(fp, "P3\n");
    fprintf(fp, "%d %d\n",width,height);
    fprintf(fp,"%d\n", maxSatVal);
    Image Im = {.fp = fp, .width = width, .height = height, .maxSatVal = maxSatVal};
    return Im;
}

void fill(Image Im, Color bg)
{
    for(int i = 0; i < Im.height; i++)
    {
        for(int j = 0; j < Im.width; j++)
        {
            writePixel(Im.fp, bg);
        }
    }
}

void drawCircle(Image Im,  Color fg, Color bg, int radius, bool center)
{
    Point Por; // POINT OF REFERENCE
    if(center)
    {
        Por.x = Im.width/2;
        Por.y = Im.height/2;
    } else{
        Por.x = 0;
        Por.y = 0;
    }
    for(int i = 0; i < Im.height; i++)
    {
        for(int j = 0; j < Im.width; j++)
        {
            if(fpow(i - Por.y,2) + fpow(j - Por.x,2) <= fpow(radius,2))
            {
                writePixel(Im.fp, fg);
            }else{
                writePixel(Im.fp, bg);
            }
        }
    }
}

void writePixel(FILE* fp, Color p)
{
    fprintf(fp, "%d %d %d\n", p.r,p.b,p.g);
}

#endif 