#include "include/raylib.h"
#include <math.h>
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define GRID_STEP 50
#define MAX_ENTITIES 5
#define FORCE_STATIC 1.0f
#define SOURCE_RADIUS 15
#define POINT_RADIUS 1
#define MAX_POINTS 1600
#define POINT_MASS 1
#define FORCE_CONSTANT 0.0000001

typedef struct
{
  Vector2 pos;
  float force;
} source;

typedef struct
{
  int counter;
  source entities[MAX_ENTITIES];
} EntityList;

typedef struct
{
  int counter;
  Vector2 pos;
  Vector2 fvec;
  Vector2 flist[MAX_ENTITIES];
} Point;

typedef struct
{
  int counter;
  Point Plane[MAX_POINTS];
} PointsList;

void SpawnSource(EntityList *e);
void Update(EntityList *e);
void PrintEntityList(EntityList *e);
void PrintPlaneList(PointsList *pl);
void InitializePoints(PointsList *pl);
float CalculateForce(source s, Vector2 e);
float GetDistance(Vector2 s, Vector2 e);
float GetMagn(Vector2 vec);
Vector2 ScalarVector(float scalar, Vector2 *vec);
void NormalizeVector(Vector2 *vec);
void ProcessPoints(PointsList *pl, EntityList *e);
void DrawPoints(PointsList *pl);
void DrawForceVectorLines(PointsList *pl, EntityList *e);
void DrawGridVec(void);

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Vector Field");
    SetTargetFPS(30);

    // INITIALIZE VARIABLES
    bool ShowGrid = false;
    bool ShowPoints = false;
    bool ShowForceLines = false;

    EntityList e;
    e.counter = 0;

    PointsList pl;
    pl.counter = 0;

    InitializePoints(&pl);

    while (!WindowShouldClose())
    {
        ClearBackground(BLACK);
        BeginDrawing();

        // DRAW TITLE
        DrawText("Vector Field", SCREEN_WIDTH / 5 * 2, SCREEN_HEIGHT / 50, 20, LIGHTGRAY);

        // DRAW GRID
        if (ShowGrid)
            DrawGridVec();
        // DISABLE GRID
        if (IsKeyPressed(KEY_G))
        {
            ShowGrid = !ShowGrid;
        }

        // DRAW POINTS
        if (ShowPoints)
        {
            DrawPoints(&pl);
        }
        // DISABLE POINTS
        if (IsKeyPressed(KEY_P))
        {
            ShowPoints = !ShowPoints;
        }

        // DRAW FORCE LINES
        if (ShowForceLines)
        {
            ProcessPoints(&pl, &e);
        }

        // DISABLE FORCE LINES
        if (IsKeyPressed(KEY_F))
        {
            ShowForceLines = !ShowForceLines;
        }

        // UPDATE
        Update(&e);

        // CREATE SOURCE
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && e.counter < MAX_ENTITIES)
        {
            SpawnSource(&e);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

// DRAWS GRID
void DrawGridVec(void)
{
    for (int x = 0; x < SCREEN_WIDTH; x += GRID_STEP)
    {
        DrawLine(x, 0, x, SCREEN_HEIGHT, LIGHTGRAY);
    }
    for (int y = 0; y < SCREEN_HEIGHT; y += GRID_STEP)
    {
        DrawLine(0, y, SCREEN_WIDTH, y, LIGHTGRAY);
    }
}

// SPAWNS SOURCE
void SpawnSource(EntityList *e)
{
    source s;
    s.pos.x = GetMouseX();
    s.pos.y = GetMouseY();
    s.force = FORCE_STATIC;
    e->entities[e->counter] = s;
    e->counter += 1;
}

// USED FOR DEBUGING
void PrintEntityList(EntityList *e)
{
    for (int i = 0; i < e->counter; i++)
    {
        printf("%f ", e->entities[i].pos.x);
        printf("%f \n", e->entities[i].pos.y);
    }
}

void PrintPlaneList(PointsList *pl)
{
    for (int i = 0; i < pl->counter; i++)
    {
        printf("%f ", pl->Plane[i].pos.x);
        printf("%f \n", pl->Plane[i].pos.y);
    }
}

// DRAWS SOURCES
void Update(EntityList *e)
{
    for (int i = 0; i < e->counter; i++)
    {
        DrawCircle(e->entities[i].pos.x, e->entities[i].pos.y, SOURCE_RADIUS, WHITE);
    }
}

void InitializePoints(PointsList *pl)
{
    for (int x = GRID_STEP / 2; x < SCREEN_WIDTH; x += GRID_STEP)
    {
        for (int y = GRID_STEP / 2; y < SCREEN_HEIGHT; y += GRID_STEP)
        {
            Point p;
            p.pos.x = x;
            p.pos.y = y;
            pl->Plane[pl->counter] = p;
            pl->counter += 1;
        }
    }
}

// DRAW THE CARTESIAN CORDINATES ON THE FIELD
void DrawPoints(PointsList *pl)
{
    for (int i = 0; i < pl->counter; i++)
    {
        DrawCircle(pl->Plane[i].pos.x, pl->Plane[i].pos.y, POINT_RADIUS, WHITE);
    }
}

void DrawForceVectorLines(PointsList *pl, EntityList *e)
{
    for (int i = 0; i < pl->counter; i++)
    {
        for (int j = 0; j < e->counter; j++)
        {
            DrawLineEx(e->entities[j].pos, pl->Plane[i].pos, 1.0f, RED);
        }
    }
}

// HELPER FUNCTIONS

float GetMagn(Vector2 vec)
{
    float magn = sqrt(pow(vec.x, 2) + pow(vec.y, 2));
    return magn;
}

void NormalizeVector(Vector2 *vec)
{
    float d = GetMagn(*vec);
    vec->x = vec->x / d;
    vec->y = vec->y / d;
}

Vector2 DistanceVec(Vector2 s, Vector2 e)
{
    Vector2 dv;
    dv.x = s.x - e.x;
    dv.y = s.y - e.y;
    NormalizeVector(&dv);
    return dv;
}

float GetDistance(Vector2 s, Vector2 e)
{
    float dx = s.x - e.x;
    float dy = s.y - e.y;
    float d = sqrt(pow(dx, 2) + pow(dy, 2));
    return d;
}

Vector2 ScalarVector(float s, Vector2 *vec)
{
    Vector2 sv;
    sv.x = vec->x * s;
    sv.y = vec->y * s;
    return sv;
}

// POINTS

void ProcessPoints(PointsList *pl, EntityList *e)
{
    for (int i = 0; i < pl->counter; i++)
    {
      for (int j = 0; j < e->counter; j++)
        {
            float f = CalculateForce(e->entities[j], pl->Plane[i].pos);
            Vector2 dv = DistanceVec(e->entities[j].pos, pl->Plane[i].pos);
	    dv = ScalarVector(15.0f, &dv);
            dv.x = dv.x + pl->Plane[i].pos.x;
            dv.y = dv.y + pl->Plane[i].pos.y;
            DrawLineEx(dv, pl->Plane[i].pos, 1.0f, RED);
        }
    }
}

// FORCE

float CalculateForce(source s, Vector2 e)
{
    float r = GetDistance(s.pos, e);
    float f = s.force / pow(r, 2) * FORCE_CONSTANT;
    return f;
}

Vector2 ForceVect(float f, Vector2 fv)
{
    fv = ScalarVector(f, &fv);
    return fv;
}
