#pragma once
#ifndef GLOBAL_HANDLER_H
#define GLOBAL_HANDLER_H

#include "Core/Definitions.hpp"
#include "Core/Window.hpp"
#include "Core/TextureLoader.hpp"
#include "Core/Camera.hpp"
#include "Core/Collisions.hpp"
#include "Entities/Character.hpp"
#include "Tilemap.hpp"

class GlobalHandler
{
    public:
        Window win;
        CameraAdv cam;
        Collisions::Master cm;
        TextureList tl;
        Map map;
        Character character;

        GlobalHandler(void)
        {
            win.SetDimensions(WIDTH,HEIGHT,WINDOW_NAME);
            win.addCustomCursor(&tl, CURSOR_TEXTURE_PATH, (Vector2){32.0f, 32.0f});
            cm.LoadBordersFromFile(BORDER_PATH_FILE);
            map.AttachGrid(GRID_FILE_PATH);
            map.AttachTextureList(&tl);
            map.AttachMap(MAP_PATH);
            character = Character("Ghosty", 0, (Vector2){64.0f, 64.0f}, &tl, "../assets/character/character.png", &cm.clb);
            character.LoadAnimationsFromFile("../assets/character/animations/assets.txt");
            character.pos = (Vector2){300.0f, 300.0f};
            ToggleFullscreen();
        }

        void Logic(void)
        {
            win.drawCursor(&tl);
        }

        void UpdateFrame(void)
        {
            character.update();
        }

        void RenderFrame(void)
        {
            this->UpdateFrame();
            this->Logic();
            BeginDrawing();
                ClearBackground(RAYWHITE);
                map.Render();
                if(DEBUG)
                {
                    map.grid.DrawGrid();
                    cm.DrawBorders();
                    character.DrawCollision();
                }
                character.Render();
                win.drawCursor(&tl);
                cam.UpdateCameraStatic();
                DrawFPS(10,10);
            EndDrawing();
        }
};

//
// GlobalHandler initGlobalHandler()
// {
//
//     // Initializing Entities
//     gh.ea = loadEntitiesFromFile(&gh.cm, &gh.tl,ENTITY_FILE_LIST);
//
//     //Loading Grid
//     gh.g = loadGridFromFile(GRID_FILE_PATH, &gh.tl);
//
//     //Initializing SpriteManager
//     InitObjectSpriteList(&gh.osl);
//
//     //Initializing Camera
//     gh.cam = initCamera2D((Vector2){0.0f, 0.0f},(Vector2){0.0f, 0.0f});
//
//     return gh;
// }

// void updateFrame(GlobalHandler* gh)
// {
//     checkCollision(&gh->cm, &gh->ea);
//     updateCameraStatic(&gh->cam, false);
//     updateEntities(&gh->ea);
//     // updateCameraFollow(&gh->cam, &gh->ea.earray[0].pos, (Vector2){WIDTH/2, HEIGHT});
// }

// void drawFrame(GlobalHandler* gh)
// {
//     ClearBackground(GRAY);
//     BeginMode2D(gh->cam);
//         drawMap(&gh->map);
//         drawSelectedTile(&gh->g, &gh->tl);
//         renderEntities(&gh->tl,&gh->ea);
//         drawCursor(&gh->win);
//         if(DEBUG)
//         {
//             drawGrid(&gh->g);
//             drawAllCollisionObjects(&gh->cm, &gh->ea);
//         }
//     EndMode2D();
//     DrawFPS(10,10);
// }

// void freeALL(GlobalHandler* gh)
// {
//     freeTextureList(&gh->tl);
//     freeGrid(&gh->g);
//     freeObjectSpriteList(&gh->osl);
// }

#endif
