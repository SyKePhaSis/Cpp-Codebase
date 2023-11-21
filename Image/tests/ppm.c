#include <stdio.h>
#include "../ppm.h"

void main()
{
    Color black = {.r = 0, .b = 0, .g = 0};
    Color purple = {.r = 255, .b = 0, .g = 255};
    Color cyan = {.r = 0, .b = 255, .g = 255};
    int width = 1024;
    int height = 1024;
    int maxSatVal = 255;
    int c_radius = 256;
    Image fp_fill;
    Image fp_circle;
    fp_fill = create("fill.ppm",width,height,maxSatVal);
    fill(fp_fill, cyan);
    fp_circle = create("circle.ppm",width,height,maxSatVal);
    drawCircle(fp_circle,purple,black,c_radius,true);
}