#ifndef TILEMAP_H
#define TILEMAP_H

#define WIDTH 960
#define HEIGHT 600
#define CAPACITY 20
#define MAX_CHARACTER_PATH 20

//INCLUDES
#include <stdio.h>
#include "../Libraries/RayLib/include/raylib.h"

//STRUCTS

typedef struct
{
    int x;
    int y;
    Texture2D texture;
} Tile;

typedef struct
{
    int height;
    int width;
    Tile **tarray;
} Grid;

typedef struct
{
    int size;
    Image *array;
} TileMap;

typedef struct
{
    Vector2 pos;
    Texture2D texture;
} Map;

#endif


// FUNCTION DEFINITIONS

////GENERATE MAP
void DrawMap(Map *map);
Map LoadMap(const char* map_file);

////GRID
void InitGrid(Grid *g);

////TILE
void CreateTile(Tile *t);

////TILEMAP
void GenerateTileMap(TileMap *tm,const char* asset_path_file);


// FUNCTIONS

void InitGrid(Grid *g)
{
    g->width = WIDTH/24;
    g->height = HEIGHT/24;
    g->tarray = malloc(g->width * g->height * sizeof(Tile*));
    if (!g->tarray){
        printf("ERROR: Memory Allocation For Grid Failed\n");
        exit(0);
    }
}

void GenerateTileMap(TileMap *tm,const char* asset_path_file)
{
    tm->size = CAPACITY;
    tm->array = malloc(CAPACITY * sizeof(Image));
    FILE *fp = fopen(asset_path_file, "r");
    char path[MAX_CHARACTER_PATH];
    if(!fp)
    {
        printf("ERROR: Couldnt open the asset file Specified!\n");
        exit(0);
    }
    int i = 0;
    while (fscanf(fp, "%s\n", path) > 0 && i < tm->size) {
        tm->array[i] =  LoadImage(path);
        i++;
    }
    if (feof(fp)) {
        printf("INFO: Tilemap successfully created! \n");
    }
    fclose(fp);
}

void CreateTiles(const char* map_file)
{}

Map LoadMap(const char* map_file)
{
    Image img = LoadImage(map_file);
    Vector2 pos = {0.0f,0.0f};
    Map map;
    map.pos = pos;
    map.texture = LoadTextureFromImage(img);
    printf("INFO: Map Loaded Successfully! \n");
    return map;
}

void DrawMap(Map *map)
{
    DrawTextureV(map->texture, map->pos, WHITE);
}
