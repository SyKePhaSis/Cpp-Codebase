#include "include/raylib.h"
#include <math.h>
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define GRID_STEP 50
#define MAX_ENTITIES 5
#define FORCE_STATIC 20.0f
#define SOURCE_RADIUS 15
#define POINT_RADIUS 1
#define MAX_POINTS 1600

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
    Vector2 pos;
    Vector2 fvec;
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
    PrintPlaneList(&pl);

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
            DrawForceVectorLines(&pl, &e);
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
    printf("%f ", e->entities[0].pos.x);
    printf("%f \n", e->entities[e->counter - 1].pos.y);
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
    printf("Started");
    printf("%i", pl->counter);
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
    for (int i = 0; i < e->counter; i++)
    {
        for (int j = 0; j < pl->counter; j++)
        {
            DrawLineEx(e->entities[i].pos, pl->Plane[j].pos, 1.0f, RED);
        }
    }
}