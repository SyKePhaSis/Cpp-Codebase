#pragma once
#ifndef TILEMAP_H
#define TILEMAP_H

//INCLUDES
#include <fstream>
#include <cstdio>
#include <cmath>

#include "../Libraries/RayLib/include/raylib.h"

#include "Core/Definitions.hpp"
#include "Core/Animation.hpp"
#include "Core/TextureLoader.hpp"

//STRUCTS
typedef struct
{
    int x;
    int y;
} GridDimensions;

class Grid {

    typedef struct
    {
        Vector2 pos; // (rows,columns)
        Rectangle r;
        Animations::ObjectAnimation oa;
    } Tile;

    typedef struct
    {
        Vector2 size;
        Animations::ObjectAnimation oa;
    } TileSelector;

    public:
        GridDimensions dimensions;// (rows,columns)
        Vector2 tileSize;
        Vector2 offset;
        Tile *tarray;
        TextureList *tl;
        bool selectorActive;
        TileSelector ts;

        Grid(){}

        Grid(Rectangle grid_area, Vector2 TileDimensions)
        {
            selectorActive = false;
            offset = (Vector2){grid_area.x, grid_area.y};
            dimensions.y = ceil(grid_area.width/TileDimensions.x);
            dimensions.x = ceil(grid_area.height/TileDimensions.y);
            tileSize.x = TileDimensions.x;
            tileSize.y = TileDimensions.y;
            tarray = (Tile*)malloc(dimensions.x * dimensions.y * sizeof(Tile));
            initializeTiles();
            printf("INFO: Allocating [%d] bytes for TileMap\n", (int)(dimensions.x * dimensions.y * sizeof(Tile)));
        }

        void AttachTextureList(TextureList *tlp)
        {
            tl = tlp;
        }

        void LoadGrid(const char* asset_file)
        {
            std::fstream dfile(asset_file);
            if(!dfile)
            {
                printf("ERROR: Couldn't open the grid asset file [%s]\n", asset_file);
            } else {
                printf("INFO: Opened the grid asset file [%s]\n", asset_file);
                Vector2 posS;
                Vector2 posE;
                Vector2 tileS;
                int tsb;
                if(dfile >> posS.x >> posS.y >> posE.x >> posE.y >> tileS.x >> tileS.y >> tsb)
                {
                    offset = posS;
                    dimensions = (GridDimensions){(int)ceil((posE.x - posS.x)/tileS.x),(int)ceil((posE.y - posS.y)/tileS.y)};
                    printf("INFO: Grid Dimensions [%d,%d]\n", dimensions.x, dimensions.y);
                    tileSize = tileS;
                    selectorActive = false;
                    tarray = (Tile*)malloc(dimensions.x * dimensions.y * sizeof(Tile));
                    initializeTiles();
                    printf("INFO: Allocating [%d] bytes for Grid\n", (int)(dimensions.x * dimensions.y * sizeof(Tile)));
                    if(tsb)
                    {
                        char asset_file[32] = {0};
                        int animLen = 0;
                        float animSpeed = 0;
                        if(dfile << asset_file << animLen << animSpeed)
                        {
                            AttachTileSelector(asset_file, animLen, animSpeed);
                        }

                    }
                    dfile.close();
                }
            }
        }

        void AttachTileSelector(TileSelector tl)
        {
            ts = tl;
        }

        void AttachTileSelector(const char* file_path, int animLen, float animSpeed)
        {
            ts.size = tileSize;
            ts.oa = Animations::ObjectAnimation();
            ts.oa.addAnimation(tl, file_path, animSpeed, animLen);
        }

        void drawSelectedTile(void)
        {
            Vector2 mousePos = GetMousePosition();
            for(int i = 0; i < dimensions.x; i++)
            {
                for(int j = 0; j < dimensions.y; j++)
                {
                    if(CheckCollisionPointRec(mousePos, tarray[i * dimensions.y + j].r))
                    {
                        Rectangle r = ts.oa.getAnimTextureCropPos();
                        r.width = r.width * ts.size.x;
                        r.height = r.height * ts.size.y;
                        r.x = r.x * ts.size.x;
                        Vector2 tilePos = (Vector2){
                            tarray[i * dimensions.y + j].r.x,
                            tarray[i * dimensions.y + j].r.y
                        };
                        Texture2D t =  tl->getTextureFromId(ts.oa.tId);
                        DrawTextureRec(t, r, tilePos, WHITE);
                    }
                }
            }
        }

        ~Grid(void)
        {
            free(tarray);
        }

        void DrawGrid(void)
        {
            for(int i = 0; i < dimensions.x; i++)
            {
                for(int j = 0; j < dimensions.y; j++)
                {
                    DrawRectangleLinesEx(tarray[i * dimensions.y + j].r, 1.0f, GREEN);
                }
            }
        }

    private:

        void initializeTiles(void)
        {
            for(int i = 0; i < dimensions.x; i++)
            {
                for(int j = 0; j < dimensions.y; j++)
                {
                    Tile t = (Tile){
                        (Vector2){(float)i,(float)j},
                        (Rectangle){
                            i * tileSize.x + offset.x,
                            j * tileSize.y + offset.y,
                            tileSize.x,
                            tileSize.y
                        }
                    };
                    tarray[i * dimensions.y + j] = t;
                }
            }
        }

        Tile* getTile(GridDimensions pos)
        {
            return &tarray[pos.x * dimensions.y + pos.y];
        }

};

class Map {
    public:
        int tid; // Texture Id
        Grid grid;
        TextureList* tl;

        Map(void){}

        Map(TextureList* tlp, const char* path)
        {
            tl = tlp;
            tid = tl->LoadTextureToList(path);
            printf("INFO: Map Loaded Successfully! \n");
        }

        void AttachMap(const char* path){
            tid = tl->LoadTextureToList(path);
            printf("INFO: Map Attached Successfully! \n");
        }

        void AttachTextureList(TextureList* tlp)
        {
            tl = tlp;
            grid.AttachTextureList(tlp);
        }

        void Render(void)
        {
            Texture2D t = tl->getTextureFromId(tid);
            DrawTextureV(t, (Vector2){0.0f, 0.0f}, WHITE);
        }

        void AttachGrid(const char* path)
        {
            grid.LoadGrid(path);
        }
};

#endif
