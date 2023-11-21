#include "../Interpolation.h"
#include <stdio.h>

int main(){
    printf(" STARTING TEST OF INTERPOLATION\n");
    TripletPoint p1 = {.x = 54.458333, .y = 17.041667, .v = 31.945};
    TripletPoint p2 = {.x = 54.458333, .y = 17.083333, .v = 31.866};
    TripletPoint p3 = {.x = 54.5, .y = 17.041667, .v = 31.993};
    TripletPoint p4 = {.x = 54.5, .y = 17.083333, .v = 31.911};
    Point p = {.x = 54.4786674627, .y = 17.0470721369};
    float a = bilerp(p1,p2,p3,p4,p);
    printf("Answer: %f", a);
}   