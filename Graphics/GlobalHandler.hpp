#pragma once
#ifndef GLOBAL_HANDLER_H
#define GLOBAL_HANDLER_H

#include "Core/Definitions.hpp"
#include "Core/Window.hpp"
#include "Core/TextureLoader.hpp"
#include "Core/Camera.hpp"
#include "Core/Collisions.hpp"
#include "Core/UIComponents.hpp"
#include "Core/Config.hpp"
#include "Entities/EntityList.hpp"

#include "Tilemap.hpp"

#include <string>
#include <memory>

class GlobalHandler
{
    public:
        Window win;
        TextureList tl;
        CameraAdv cam;
        Collisions::Master cm;
        Map map;
        UI::UIParent uiroot;
        Config config;
        EntityList el;

        GlobalHandler(void)
        {


            config.LoadConfig("../include/config.ini");

            win.SetParameters(std::stoi(config.GetValue("WIDTH")), std::stoi(config.GetValue("HEIGHT")), config.GetValue("TITLE"));
            win.addCustomCursor(&tl, config.GetValue("CURSOR_TEXTURE_PATH"), (Vector2){32.0f, 32.0f});

            cm.LoadBordersFromFile(config.GetValue("BORDER_PATH_FILE"));

            map.AttachTextureList(&tl);
            map.AttachGrid(config.GetValue("GRID_FILE_PATH"));
            map.AttachMap(config.GetValue("MAP_PATH"));

            el.AttachAll(&cm.bv, tl, config);
            el.LoadEntitiesFromFile(config.GetValue("ENTITY_FILE_LIST"));
            ToggleFullscreen();
        }

        void Logic(void)
        {

        }

        void UpdateFrame(void)
        {
            el.Update();
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
                    }
                    map.grid.DrawSelectedTile();
                    el.Render();
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
