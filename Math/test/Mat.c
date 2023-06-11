#include "../Mat.h"

int main()
{

    matrix m = MatAllocate(2, 2);
    matrix m2 = MatAllocate(4, 8);
    matrix m3 = MatAllocate(2, 2);
    matrix m4 = MatAllocate(2, 2);

    MatRand(m, 0, 10);
    MatRand(m2, 5, 10);
    MatFill(m3, 7);

    MatPrint(m);
    MatPrint(m2);
    MatPrint(m3);

    m4 = MatAdd(m, m3);
    MatPrint(m4);

    MatFill(m4, 10);
    MatPrint(m4);

    MatScalarMult(m4,3);
    MatPrint(m4);
    return 0;
}
