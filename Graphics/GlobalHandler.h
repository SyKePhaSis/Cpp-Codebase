#ifndef GLOBAL_HANDLER_H
#define GLOBAL_HANDLER_H

#include "Core/Definitions.h"
#include "Core/Window.h"
#include "Core/TextureLoader.h"
#include "Core/Camera.h"
#include "Collisions.h"
#include "EntityHandler.h"
#include "Sprite.h"
#include "Tilemap.h"

typedef struct {
    Window win;
    Camera2D cam;
    EntityArray ea;
    CollisionMaster cm;
    ObjectSpriteList osl;
    Grid g;
    TextureList tl;
    Map map;
} GlobalHandler;

GlobalHandler initGlobalHandler(Window win)
{
    GlobalHandler gh;

    // Initialize  Texture List
    gh.tl = initTextureList();

    // Initialize Window
    gh.win = win;
    InitWin(&gh.win);
    addCustomCursor(&gh.win, CURSOR_TEXTURE_PATH, (Vector2){32.0f, 32.0f});

    // Initializing CollisionMaster
    gh.cm = initCollision();
    loadBordersFromFile(&gh.cm, BORDER_PATH_FILE);

    // Initializing Entities
    gh.ea = loadEntitiesFromFile(&gh.cm, &gh.tl,ENTITY_FILE_LIST);

    //Initializing Map
    gh.map = loadMap(MAP_PATH);

    //Loading Grid
    gh.g = loadGridFromFile(GRID_FILE_PATH);

    //Initializing SpriteManager
    InitObjectSpriteList(&gh.osl);

    //Initializing Camera
    gh.cam = initCamera2D((Vector2){0.0f, 0.0f},(Vector2){0.0f, 0.0f});

    return gh;
}

void gameLogic(void)
{
    if(IsCursorOnScreen())
    {
        HideCursor();
    } else {
        ShowCursor();
    }
}

void updateFrame(GlobalHandler* gh)
{
    checkCollision(&gh->cm, &gh->ea);
    updateCameraStatic(&gh->cam, false);
    updateEntities(&gh->ea);
    // updateCameraFollow(&gh->cam, &gh->ea.earray[0].pos, (Vector2){WIDTH, HEIGHT});
}

void drawFrame(GlobalHandler* gh)
{
    ClearBackground(GRAY);
    BeginMode2D(gh->cam);
        drawMap(&gh->map);
        drawSelectedTile(&gh->g);
        renderEntities(&gh->tl,&gh->ea);
        drawCursor(&gh->win);
        if(DEBUG)
        {
            drawGrid(&gh->g);
            drawAllCollisionObjects(&gh->cm, &gh->ea);
        }
    EndMode2D();
    DrawFPS(10,10);
}

void freeALL(GlobalHandler* gh)
{
    freeTextureList(&gh->tl);
    freeGrid(&gh->g);
    freeObjectSpriteList(&gh->osl);
}

#endif
