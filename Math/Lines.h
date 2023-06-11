#ifndef LINES_H
#define LINES_H

#include "Mat.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

//LINE EQUATION Y = Mx + b
typedef struct
{
  float slope;
  float b;
} Line;

typedef struct
{
  float x;
  float y;
} Point;

//TRANSFORM 2x1 MATRIX TO LINE EQ
Line MatToLine(matrix m)
{
  if(m.rows == 2 && m.columns == 1)
    {
      Line l;
      l.slope = MatAt(m,0,0);
      l.b = MatAt(m,1,0);
      return l;
    }
  else
    {
      printf("[ERROR]Matrix not compatable!\n");
      printf("[EXITING]");
      exit(0);
    }
}

//TRANSFORM LINE TO MATRIX
matrix LineToMat(Line l)
{
  matrix m = MatAllocate(2,1);
  MatAt(m,0,0) = l.slope;
  MatAt(m,1,0) = l.b;
  return m;
}

//CHECK IF POINT IS ON THE LINE 
bool PointOnLine(Point p, Line l)
{
  float y = l.slope*p.x + l.b;
  if(p.y == y)
    {
      return true;
    }
  else
    {
      return false;
    }
}

//CALCULATE LINE FROM POINTS
Line LineFromPoints(Point p1, Point p2)
{
  Line l;
  float slope = (p1.y - p2.y)/(p1.x - p2.x);
  float b = p1.y - slope*p1.x;
  l.slope = slope;
  l.b = b;
  return l;
}

//PRINT LINE
void LinePrint(Line l)
{
  printf("Equation: y = %fx + %f\n", l.slope, l.b);
  printf("Matrix Representation: ");
  matrix m = LineToMat(l);
  MatPrint(m);
}

#endif
