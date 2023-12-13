#pragma once
#ifndef UICOMPONENTS_H
#define UICOMPONENTS_H

#include "../../Libraries/RayLib/include/raylib.h"
#include "TextureLoader.hpp"

#include <string>
#include <vector>
#include <cstdbool>
#include <fstream>
#include <memory>

namespace UI {

    class UIComponent {
        public:
            Vector2 size;
            Vector2 pos;
            bool show;

            UIComponent(){}

            //Visibility
            void ToggleVisibility(void)
            {
                show = !show;
            }

            //Drawing
            virtual void Render(void)
            {}
    };

    namespace Components{

        class Texture : public UIComponent{
            public:
                int textId;
                TextureList *tl;

                Texture(void){}

                Texture(TextureList *tlp, const char* path ,Vector2 Csize, Vector2 Cpos)
                {
                    this->AttachTextureList(tlp);
                    this->AttachTexture(path);
                    size = Csize;
                    pos = Cpos;
                    show = true;
                }

                void AttachTextureList(TextureList *tlp)
                {
                    tl = tlp;
                }

                void AttachTexture(const char* path)
                {
                    if(!tl)
                    {
                        printf("ERROR: Texture List Not Attached\n");
                    } else {
                        textId = tl->LoadTextureToList(path);
                    }
                }

                void Render(void)
                {
                    Texture2D t = tl->getTextureFromId(textId);
                    DrawTextureV(t, pos, WHITE);
                }
        };

        class Button : public Texture {
            public:
                Button(void){}

                Button(TextureList *tlp, const char* path ,Vector2 Csize, Vector2 Cpos)
                {
                    this->AttachTextureList(tlp);
                    this->AttachTexture(path);
                    size = Csize;
                    pos = Cpos;
                    show = true;
                }

                void Action(void)
                {
                    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        Vector2 Mpos = GetMousePosition();
                        if(CheckCollisionPointRec(Mpos, (Rectangle){pos.x, pos.y, size.x, size.y}))
                        {
                            printf("Action");
                        }
                    }
                }
        };
    };

    class UIParent: public UIComponent{
        public:
            std::string name;
            TextureList *tl;
            std::vector<std::shared_ptr<UIComponent>> children;

            UIParent(void)
            {
                size = (Vector2){0.0f, 0.0f};
                pos = (Vector2){0.0f, 0.0f};
                name = "";
                show = true;
            }

            UIParent(const char* n, Vector2 Cpos, Vector2 Csize)
            {
                name = n;
                pos = Cpos;
                size = Csize;
                show = true;
            }

            //Methods
            void AddComponent(std::shared_ptr<UIComponent> uic)
            {
                printf("INFO: Pushed Back!\n");
                children.push_back(uic);
            }

            void AttachTextureList(TextureList *tlp)
            {
                tl = tlp;
            }

            //Loading
            void LoadUIComponentsFromFile(const char* path)
            {
                std::fstream dfile(path);
                if(!dfile)
                {
                    printf("ERROR: Couldn't Open UIComponent File [%s]\n", path);
                }
                else {
                    printf("INFO: Opened UIComponent File [%s]\n", path);
                    char type[32];
                    while(dfile >> type)
                    {
                        if(strcmp(type, "Texture") == 0)
                        {
                            char path[64];
                            Vector2 pos;
                            Vector2 size;
                            if(dfile >> path >> pos.x >> pos.y >> size.x >> size.y)
                            {
                                Components::Texture t(tl,path,size,pos);
                                std::shared_ptr<UI::UIComponent> ptr(&t);
                                this->AddComponent(ptr);
                            }
                        }
                    }
                }
                dfile.close();
            }

            //Visibility
            void ToggleVisibility(void)
            {
                show = !show;
            }

            //Drawing

            void Render(void)
            {
                if(show)
                {
                    for(auto&& component: children)
                    {
                        component->Render();
                    }
                }
            }
    };
};

#endif
