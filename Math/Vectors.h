#ifndef VECTORS_2D
#define VECTORS_2D

#include <math.h>
#include <stdio.h>

typedef struct
{
  float x;
  float y;
}Vector2;

//DECLARATION OF FUNCTIONS

float VSize(Vector2 v);
void  VScalarMult(Vector2* v, float f);
float VGetAngle(Vector2 v, Vector2 f);
float Vdot(Vector2 v, Vector2 f);
void  VNormalize(Vector2* v);
void VPrint(Vector2 v);

//FUNCTIONS
float VSize(Vector2 v)
{
  float d = sqrt(pow(v.x,2) + pow(v.y,2));
  return d;
}

void VScalarMult(Vector2* v, float f)
{
  v->x = v->x * f;
  v->y = v->y * f;
}

float VGetAngle(Vector2 v, Vector2 f)
{
  float vd = VSize(v);
  float fd = VSize(f);
  float dot = Vdot(v,f);
  float a = acos(dot/(vd * fd));
  return a;
}

float Vdot(Vector2 v, Vector2 f)
{
  float dot = v.x*f.x + v.y*f.y;
  return dot;
}

void VNormalize(Vector2* v)
{
  float d = VSize(*v);
  v->x = v->x/d;
  v->y = v->y/d;
}

void VPrint(Vector2 v)
{
  printf(" <%f,%f> ",v.x,v.y);
}

#endif
