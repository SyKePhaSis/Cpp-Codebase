#ifndef TILEMAP_H
#define TILEMAP_H

#define WIDTH 960
#define HEIGHT 600
#define CAPACITY 20
#define MAX_CHARACTER_PATH 20
#define TILE_WIDTH 24
#define TILE_HEIGHT 24

//INCLUDES
#include <stdio.h>
#include <math.h>
#include "../Libraries/RayLib/include/raylib.h"

//STRUCTS

typedef struct
{
    int x;
    int y;
} GridDimensions;

typedef struct
{
    Vector2 pos; // (rows,columns)
    Rectangle r;
    Texture2D texture;
} Tile;

typedef struct
{
    GridDimensions dimensions;// (rows,columns)
    Vector2 offset;
    Tile *tarray;
} Grid;

typedef struct
{
    Vector2 pos;
    Texture2D texture;
} Map;

#endif


// FUNCTION DEFINITIONS

// - MAP FUNCTIONS
void drawMap(Map *map);
Map loadMap(const char* map_file);

// - GRID FUNCTIONS
Grid initGrid(Rectangle grid_area);
void drawGrid(Grid *g);
void freeGrid(Grid* g);

// - TILE FUNCTIONS
void initTiles(Grid* g);
Tile* GetTile(Grid *g, GridDimensions pos);
void LoadTextureToTile(Grid *g, GridDimensions pos, Texture2D text);

// FUNCTIONS

Grid initGrid(Rectangle grid_area)
{
    Grid g;
    g.offset = (Vector2){grid_area.x, grid_area.y};
    g.dimensions.x = grid_area.width/TILE_WIDTH;
    g.dimensions.y = grid_area.height/TILE_HEIGHT;
    g.tarray = malloc(g.dimensions.x * g.dimensions.y * sizeof(Tile));
    printf("INFO: Allocating %d bytes for TileMap\n", (int)(g.dimensions.x * g.dimensions.y * sizeof(Tile)));
    if (!g.tarray){
        printf("ERROR: Memory Allocation For Grid Failed\n");
        exit(0);
    } else {
        initTiles(&g);
    }
    return g;
}

void drawGrid(Grid *g)
{
    for(int i = 0; i < g->dimensions.y; i++)
    {
        for(int j = 0; j < g->dimensions.x; j++)
        {
            DrawRectangleLinesEx(g->tarray[i * g->dimensions.x + j].r, 0.5f, GREEN);
        }
    }
}

void initTiles(Grid* g)
{
    for(int i = 0; i < g->dimensions.y; i++)
    {
        for(int j = 0; j < g->dimensions.x; j++)
        {
            Tile t = (Tile){
                i,
                j,
                (Rectangle){
                    j * TILE_WIDTH + g->offset.x,
                    i * TILE_HEIGHT + g->offset.y,
                    TILE_WIDTH,
                    TILE_HEIGHT
                }
            };
            g->tarray[i * g->dimensions.x + j] = t;
        }
    }
}

Tile* GetTile(Grid *g, GridDimensions pos)
{
    Tile *t = &g->tarray[pos.x * g->dimensions.y + pos.y];
    return t;
}

void LoadTextureToTile(Grid *g,  GridDimensions pos, Texture2D text)
{
    Tile* t = GetTile(g, pos);
    t->texture = text;
}

void freeGrid(Grid* g)
{
    free(g->tarray);
    free(g);
}

Map loadMap(const char* map_file)
{
    Image img = LoadImage(map_file);
    Vector2 pos = {0.0f,0.0f};
    Map map;
    map.pos = pos;
    map.texture = LoadTextureFromImage(img);
    printf("INFO: Map Loaded Successfully! \n");
    return map;
}

void drawMap(Map *map)
{
    DrawTextureV(map->texture, map->pos, WHITE);
}
