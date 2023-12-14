#pragma once
#ifndef GLOBAL_HANDLER_H
#define GLOBAL_HANDLER_H

#include "Core/Definitions.hpp"
#include "Core/Window.hpp"
#include "Core/TextureLoader.hpp"
#include "Core/Camera.hpp"
#include "Core/Collisions.hpp"
#include "Core/UIComponents.hpp"
#include "Entities/Character.hpp"
#include "Tilemap.hpp"

class GlobalHandler
{
    public:
        Window win {WIDTH,HEIGHT,WINDOW_NAME};
        TextureList tl;
        CameraAdv cam;
        Collisions::Master cm;
        Map map;
        Character character;
        UI::UIParent uiroot;

        GlobalHandler(void)
        {
            win.addCustomCursor(&tl, CURSOR_TEXTURE_PATH, (Vector2){32.0f, 32.0f});

            cm.LoadBordersFromFile(BORDER_PATH_FILE);

            map.AttachTextureList(&tl);
            map.AttachGrid(GRID_FILE_PATH);
            map.AttachMap(MAP_PATH);

            character = Character("Ghosty", 0, (Vector2){64.0f, 64.0f}, &tl, "../assets/character/character.png", &cm.bv);
            character.LoadAnimationsFromFile("../assets/character/animations/assets.txt");
            character.pos = (Vector2){300.0f, 300.0f};
            character.AttachEntitySelector("../assets/character/selector.txt");

            ToggleFullscreen();
        }

        void Logic(void)
        {
        }

        void UpdateFrame(void)
        {
            character.update();
            uiroot.Update();
            map.Update();
        }

        void RenderFrame(void)
        {
            this->UpdateFrame();
            this->Logic();
            BeginDrawing();
                if(!UI_ONLY)
                {
                    ClearBackground(RAYWHITE);
                    map.Render();
                    if(DEBUG)
                    {
                        map.grid.DrawGrid();
                        cm.DrawBorders();
                        character.DrawCollision();
                    }
                    map.grid.DrawSelectedTile();
                    character.Render();
                    uiroot.Render();
                    win.drawCursor(&tl);
                    cam.UpdateCameraStatic();
                    DrawFPS(10,10);
                }
                else {
                    ClearBackground(BLACK);
                    uiroot.Render();
                    win.drawCursor(&tl);
                }
            EndDrawing();
        }
};

#endif
