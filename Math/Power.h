#ifndef POWER
#define POWER

//INCLUDES

//STRUCT

//FUNCTION DECLARATIONS
float fpow(int base, int exp);

//FUNCTIONS
float fpow(int base, int exp)
{
    int p = base;
    for(int i = 1; i < exp; i++)
    {
        p *= base;
    }
    return p;
}

#endif 