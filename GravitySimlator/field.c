#include "include/raylib.h"
#include <math.h>
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define GRID_STEP 200
#define MAX_ENTITIES 5
#define FORCE_STATIC 20.0f
#define SOURCE_RADIUS 25
#define POINT_RADIUS 2

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
    Point Plane[];
} PointsList;

void DrawGridVec(void);
void SpawnSource(EntityList *e);
void Update(EntityList *e);
void printEntityList(EntityList *e);
void InitializePoints(PointsList *pl);
void DrawPoints(PointsList *pl);

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Vector Field");
    SetTargetFPS(30);

    // INITIALIZE VARIABLES
    bool ShowGrid = true;
    bool ShowPoints = false;

    EntityList e;
    e.counter = 0;

    PointsList pl;
    pl.counter = 0;

    InitializePoints(&pl);

    while (!WindowShouldClose())
    {
        // ClearBackground(BLACK);
        BeginDrawing();

        // DRAW TITLE
        DrawText("Vector Field", SCREEN_WIDTH / 5 * 2, SCREEN_HEIGHT / 50, 20, LIGHTGRAY);

        // DRAW GRID
        if (ShowGrid)
            DrawGridVec();
        // DISABLE GRID
        if (IsKeyPressed(KEY_G))
        {
            ShowGrid = false;
        }

        // DRAW POINTS
        if (ShowPoints)
        {
            printf("Cant Handle This Shit");
            DrawPoints(&pl);
        }
        // DISABLE POINTS
        if (IsKeyPressed(KEY_P))
        {
            ShowPoints = false;
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
void printEntityList(EntityList *e)
{
    for (int i = 0; i < e->counter; i++)
    {
        printf("%f ", e->entities[i].pos.x);
        printf("%f \n", e->entities[i].pos.y);
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
    for (int x = GRID_STEP / 2; x < (SCREEN_WIDTH - GRID_STEP / 2); x += GRID_STEP)
    {
        for (int y = GRID_STEP / 2; y < (SCREEN_HEIGHT - GRID_STEP / 2); y += GRID_STEP)
        {
            Point p;
            p.pos.x = x;
            p.pos.y = y;
            pl->Plane[pl->counter] = p;
            pl->counter += 1;
        }
    }
    printf("Finished Initializing");
}

void DrawPoints(PointsList *pl)
{
    for (int i = 0; i < pl->counter; i++)
    {
        DrawCircle(pl->Plane[i].pos.x, pl->Plane[i].pos.y, POINT_RADIUS, WHITE);
    }
}