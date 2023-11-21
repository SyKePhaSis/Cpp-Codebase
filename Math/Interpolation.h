#ifndef INTERPOLATION_H
#define INTERPOLATION_H

//INCLUDES
#include <stdio.h>

//STRUCTS 
typedef struct
{
  float x;
  float y;
} Point;

typedef struct
{
  float x;
  float y;
  float v; //VALUE
} TripletPoint;

//FUNCTION DEFINITIONS
float lerp(float a, float b, float p);
float bilerp(TripletPoint p1, TripletPoint p2, TripletPoint p3, TripletPoint p4, Point p);
TripletPoint Lerp2D(TripletPoint a, TripletPoint b, Point p);
Point reversePoint(Point x);
TripletPoint reverseTripletPoint(TripletPoint x);

//FUNCTIONS
Point reversePoint(Point p)
{
    float tmp = p.x;
    p.x = p.y;
    p.y = tmp;
    return p;
}

TripletPoint reverseTripletPoint(TripletPoint p)
{
    float tmp = p.x;
    p.x = p.y;
    p.y = tmp;
    return p;
}

float lerp(float a, float b, float p)
{
    return a + (b - a)*p;
}

TripletPoint Lerp2D(TripletPoint a, TripletPoint b, Point p)
{
    TripletPoint r;
    r.v = (a.v*(b.x - p.x) + b.v*(p.x - a.x))/(b.x - a.x);
    r.y = a.y;
    r.x = p.x;
    return r;
}

// p1.y == p3.y, p2.y == p4.y
float bilerp(TripletPoint p1, TripletPoint p2, TripletPoint p3, TripletPoint p4, Point p)
{
    TripletPoint R1 = Lerp2D(p1,p3,p);
    TripletPoint R2 = Lerp2D(p2,p4,p);
    R1 = reverseTripletPoint(R1);
    R2 = reverseTripletPoint(R2);
    p = reversePoint(p);
    TripletPoint R = Lerp2D(R1,R2,p);
    R = reverseTripletPoint(R);
    return R.v;
}

#endif