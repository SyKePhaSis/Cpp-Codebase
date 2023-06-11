#include "../Lines.h"

int main(){
  printf(" STARTING TESTING ON LINES\n");
  
  //GENERATE LINE AND POINTS
  Point p1;
  p1.x = 1;
  p1.y = 1;

  Point p2;
  p2.x = 2;
  p2.y = 4;

  Line lm;
  lm.slope = 1;
  lm.b = 0;

  Line l;

  matrix ml;
  ml = MatAllocate(2,1);
  MatAt(ml,0,0) = 1;
  MatAt(ml,1,0) = 2;

  matrix m;

  //TEST MAT_TO_LINE
  l = MatToLine(ml);
  LinePrint(l);

  //TEST LINE_TO_MAT
  printf("\nTransforming line(y = %fx + %f) to matrix.\n", lm.slope, lm.b);
  m = LineToMat(lm);
  printf("The Matrix:");
  MatPrint(m);

  //TEST POINT ON LINE
  if(PointOnLine(p1,lm))
    {
      printf("Point(<%f,%f>) is on line(y = %fx + %f).\n", p1.x, p1.y, lm.slope, lm.b);
    }
  else
    {
      printf("Point(<%f,%f>) is NOT on line(y = %fx + %f).\n", p1.x, p1.y, lm.slope, lm.b);
    }
  if(PointOnLine(p2,lm))
    {
      printf("Point(<%f,%f>) is on line(y = %fx + %f).\n", p2.x, p2.y, lm.slope, lm.b);
    }
  else
    {
      printf("Point(<%f,%f>) is NOT on line(y = %fx + %f).\n", p2.x, p2.y, lm.slope, lm.b);
    }

  //TEST LINE FROM POINTS
  Line l1;
  l1 = LineFromPoints(p1,p2);
  printf("\n");
  LinePrint(l1);
  if(PointOnLine(p1,l1))
  {
    printf("Point(<%f,%f>) is on line(y = %fx + %f).\n", p1.x, p1.y, l1.slope, l1.b);
  }
  else
  {
    printf("Point(<%f,%f>) is NOT on line(y = %fx + %f).\n", p1.x, p1.y, l1.slope, l1.b);
  }
  if(PointOnLine(p2,l1))
  {
    printf("Point(<%f,%f>) is on line(y = %fx + %f).\n", p2.x, p2.y, l1.slope, l1.b);
  }
  else
  {
    printf("Point(<%f,%f>) is NOT on line(y = %fx + %f).\n", p2.x, p2.y, l1.slope, l1.b);
  }
    
  return 0;
}

