#ifndef TILEMAP_H
#define TILEMAP_H

//INCLUDES
#include <stdio.h>
#include <math.h>
#include "../Libraries/RayLib/include/raylib.h"
#include "Core/Definitions.h"
#include "Core/Animation.h"

//STRUCTS

typedef struct
{
    int x;
    int y;
} GridDimensions;

typedef struct
{
    Vector2 size;
    ObjectAnimation oa;
} TileSelector;

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
    int tl_active;
    TileSelector tl;
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
Grid loadGridFromFile(const char* asset_file);
void updateGrid(Grid *g);
void drawGrid(Grid *g);
void freeGrid(Grid* g);

// - TILE FUNCTIONS
void initTiles(Grid* g);
void initTileSelector(Grid* g, const char* file_path, int animLen, float animSpeed);
Tile* GetTile(Grid *g, GridDimensions pos);
void LoadTextureToTile(Grid *g, GridDimensions pos, Texture2D text);

// FUNCTIONS

Grid initGrid(Rectangle grid_area)
{
    Grid g;
    g.tl_active = 0;
    g.offset = (Vector2){grid_area.x, grid_area.y};
    g.dimensions.y = grid_area.width/TILE_WIDTH;
    g.dimensions.x = grid_area.height/TILE_HEIGHT;
    g.tarray = malloc(g.dimensions.x * g.dimensions.y * sizeof(Tile));
    printf("INFO: Allocating [%d] bytes for TileMap\n", (int)(g.dimensions.x * g.dimensions.y * sizeof(Tile)));
    if (!g.tarray){
        printf("ERROR: Memory Allocation For Grid Failed\n");
        exit(0);
    } else {
        initTiles(&g);
    }
    return g;
}

void initTileSelector(Grid* g, const char* file_path, int animLen, float animSpeed)
{
    g->tl_active = 1;
    TileSelector tl;
    tl.size = (Vector2){TILE_WIDTH, TILE_HEIGHT};
    tl.oa.sprite = LoadTexture(file_path);
    tl.oa.animSpeed = animSpeed;
    tl.oa.animLen = animLen;
    g->tl = tl;
}

Grid loadGridFromFile(const char* asset_file)
{
    FILE *fp = fopen(asset_file, "r");
    if(!fp)
    {
        printf("ERROR: Couldn't open the grid asset file [%s]\n", asset_file);
    } else {
        printf("INFO: Opened the grid asset file [%s]\n", asset_file);
        Vector2 posS;
        Vector2 posE;
        int tl;
        if(fscanf(fp,"%f%f%f%f%d", &posS.x, &posS.y, &posE.x, &posE.y, &tl) == 5)
        {
            Rectangle r = (Rectangle){posS.x, posS.y, posE.x - posS.x, posE.y - posS.y};
            Grid g = initGrid(r);
            if(tl)
            {
                char asset_file[32];
                int animLen;
                float animSpeed;
                if(fscanf(fp,"%s%d%f", asset_file, &animLen, &animSpeed) == 3)
                {
                    initTileSelector(&g, asset_file, animLen, animSpeed);
                }
            }
            fclose(fp);
            return g;
        }
    }
    exit(0);
}

void drawSelectedTile(Grid *g)
{
    Vector2 mousePos = GetMousePosition();
    for(int i = 0; i < g->dimensions.x; i++)
    {
        for(int j = 0; j < g->dimensions.y; j++)
        {
            if(CheckCollisionPointRec(mousePos, g->tarray[i * g->dimensions.y + j].r))
            {
                Rectangle s = getAnimTextPosOA(&g->tl.oa);
                s.width = s.width * g->tl.size.x;
                s.height = s.height * g->tl.size.y;
                s.x = s.x * g->tl.size.x;
                Vector2 tilePos = (Vector2){
                    g->tarray[i * g->dimensions.y + j].r.x,
                    g->tarray[i * g->dimensions.y + j].r.y
                };
                DrawTextureRec(g->tl.oa.sprite, s, tilePos, WHITE);
            }
        }
    }
}

void drawGrid(Grid *g)
{
    for(int i = 0; i < g->dimensions.x; i++)
    {
        for(int j = 0; j < g->dimensions.y; j++)
        {
            DrawRectangleLinesEx(g->tarray[i * g->dimensions.y + j].r, 0.5f, GREEN);
        }
    }
}

void initTiles(Grid* g)
{
    for(int i = 0; i < g->dimensions.x; i++)
    {
        for(int j = 0; j < g->dimensions.y; j++)
        {
            Tile t = (Tile){
                (Vector2){i,j},
                (Rectangle){
                    j * TILE_WIDTH + g->offset.x,
                    i * TILE_HEIGHT + g->offset.y,
                    TILE_WIDTH,
                    TILE_HEIGHT
                }
            };
            g->tarray[i * g->dimensions.y + j] = t;
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
