#include "../Vectors.h"
#include <stdio.h>

int main()
{
  Vector2 vec;
  Vector2 fec;
  
  //TEST SIZE
  printf("Setting the v vector to:");
  vec.x = 3;
  vec.y = 4;
  VPrint(vec);
  float size = VSize(vec);
  printf("\nSize = %f\n", size);

  //TEST SCALAR MULTIPLICATION
  printf("Multiplying v vector:");
  VPrint(vec);
  printf("with the number 4\n");
  VScalarMult(&vec, 4);
  printf("The new vector is:");
  VPrint(vec);

  //TEST ANGLE BETWEEN VECTORS
  
  printf("\nSetting the f vector to:");
  fec.x = 6;
  fec.y = 10;
  VPrint(fec);
  printf("\nThe angle between the two Vectors (v,f) is: %f rad\n", VGetAngle(vec,fec));

  //TESTING DOT PRODUCT
  printf("The dot product of v and f is: %f\n", Vdot(vec,fec));

  //TESTING NORMALIZATION
  printf("The Normalized v Vector is:");
  VNormalize(&vec);
  VPrint(vec);
  printf("\nSize = %f", VSize(vec));
  
  return 1;
}
