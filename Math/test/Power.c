#include "../Power.h"
#include <stdio.h>

void main(){
    float b = 2;
    int exp = 3;
    float ans = pow(b,exp);
    printf("%f**%d = %f", b,exp,ans);
}