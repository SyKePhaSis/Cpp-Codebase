#pragma once
#ifndef TILEMAP_H
#define TILEMAP_H

//INCLUDES
#include <fstream>
#include <cstdio>
#include <cmath>
#include <string>

#include "../Libraries/RayLib/include/raylib.h"

#include "Core/Definitions.hpp"
#include "Core/Animation.hpp"
#include "Core/TextureLoader.hpp"

#include <memory>
#include <vector>

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
        Vector2 spacing;
        Vector2 tileSize;
        Vector2 offset;
        std::vector<std::vector<Tile>> tv;
        TextureList *tl;
        bool selectorActive;
        TileSelector ts;

        Grid(){}

        Grid(Rectangle grid_area, Vector2 TileDimensions)
        {
            this->selectorActive = false;
            this->offset = (Vector2){grid_area.x, grid_area.y};
            this->dimensions.y = ceil(grid_area.width/TileDimensions.x);
            this->dimensions.x = ceil(grid_area.height/TileDimensions.y);
            this->tileSize.x = TileDimensions.x;
            this->tileSize.y = TileDimensions.y;
            this->spacing = (Vector2){0.0f, 0.0f};
            initializeTiles();
            printf("INFO: Allocating [%d] bytes for TileMap\n", (int)(dimensions.x * dimensions.y * sizeof(Tile)));
        }

        void AddSpacing(void)
        {

        }

        void AttachTextureList(TextureList *tlp)
        {
            tl = tlp;
        }

        void LoadGrid(std::string asset_file)
        {
            std::fstream dfile(asset_file);
            if(!dfile)
            {
                printf("ERROR: Couldn't open the grid asset file [%s]\n", asset_file.c_str());
            } else {
                printf("INFO: Opened the grid asset file [%s]\n", asset_file.c_str());
                Vector2 posS;
                Vector2 posE;
                Vector2 tileS;
                int tsb;
                if(dfile >> posS.x >> posS.y >> posE.x >> posE.y >> tileS.x >> tileS.y >> tsb)
                {
                    this->offset = posS;
                    this->dimensions = (GridDimensions){(int)ceil((posE.x - posS.x)/tileS.x),(int)ceil((posE.y - posS.y)/tileS.y)};
                    printf("INFO: Grid Dimensions [%d,%d]\n", dimensions.x, dimensions.y);
                    this->tileSize = tileS;
                    this->selectorActive = false;
                    this->spacing = (Vector2){0.0f, 0.0f};
                    initializeTiles();
                    printf("INFO: Allocating [%d] bytes for Grid\n", (int)(dimensions.x * dimensions.y * sizeof(Tile)));
                    if(tsb)
                    {
                        char asset_file[64];
                        int animLen;
                        float animSpeed;
                        if(dfile >> asset_file >> animLen >> animSpeed)
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
            if(!tl)
            {
                printf("ERROR: TextureList not Attached In Grid!");
            }else
            {
                ts.oa.addAnimation(tl, file_path, animSpeed, animLen);
            }
        }

        void DrawSelectedTile(void)
        {
            Vector2 mousePos = GetMousePosition();
            for(auto& row: tv)
            {
                for(auto& tile: row)
                {
                    if(CheckCollisionPointRec(mousePos, tile.r))
                    {
                        Rectangle r = ts.oa.getAnimTextureCropPos();
                        r.width = r.width * ts.size.x;
                        r.height = r.height * ts.size.y;
                        r.x = r.x * ts.size.x;
                        Vector2 tilePos = (Vector2){
                            tile.r.x,
                            tile.r.y
                        };
                        Texture2D t =  tl->getTextureFromId(ts.oa.tId);
                        DrawTextureRec(t, r, tilePos, WHITE);
                    }
                }
            }
        }

        void Update(void)
        {
            this->ts.oa.updateAnimation();
        }

        void DrawGrid(void)
        {
            for(auto& row: tv)
            {
                for(auto& tile: row)
                {
                    DrawRectangleLinesEx(tile.r, 1.0f, GREEN);
                }
            }
        }

    private:

        void initializeTiles(void)
        {
            for(int i = 0; i < dimensions.x; i++)
            {
                std::vector<Tile> row;
                for(int j = 0; j < dimensions.y; j++)
                {
                    Tile t = (Tile){
                        (Vector2){(float)i,(float)j},
                        (Rectangle){
                            i * (tileSize.x + this->spacing.x) + offset.x,
                            j * (tileSize.y + this->spacing.y) + offset.y,
                            tileSize.x,
                            tileSize.y
                        }
                    };
                    row.push_back(t);
                }
                tv.push_back(row);
            }
        }

        Tile* getTile(GridDimensions pos)
        {
            return &tv.at(pos.x).at(pos.y);
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

        void AttachMap(std::string path){
            tid = tl->LoadTextureToList(path);
            printf("INFO: Map Attached Successfully! \n");
        }

        void Update(void)
        {
            this->grid.Update();
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

        void AttachGrid(std::string path)
        {
            grid.LoadGrid(path);
        }
};

#endif
