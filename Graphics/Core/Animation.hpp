#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H

//INCLUDES
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <vector>

#include "../../Libraries/RayLib/include/raylib.h"
#include "TextureLoader.hpp"
#include "Definitions.hpp"

namespace Animations {
    class CharacterAnimation{

        public:
            bool AnimationsLoaded;
            int animIndex;
            std::vector<float> animSpeed;
            std::vector<int> animLen;
            int animfCounter;
            std::vector<int> tidarray;
            int index;

            CharacterAnimation(void)
            {
                index = 0;
                animIndex = 0;
                animfCounter = 0;
            }

            void addAnimation(int tid, float animationSpeed, int animationLen)
            {
                tidarray.push_back(tid);
                animSpeed.push_back(animationSpeed);
                animLen.push_back(animationLen);
                AnimationsLoaded = true;
                printf("INFO: Added Animation!");
            }

            void changeIndex(int newIndex)
            {
                if(index != newIndex)
                {
                    index = newIndex;
                    animfCounter = 0;
                    animIndex = 0;
                }
            }

            void loadFromAssetFile(TextureList* tl, std::string asset_file_path)
            {
                std::ifstream fdata(asset_file_path);
                if(!fdata)
                {
                    printf("ERROR: Couldn't Load Asset Files\n");
                } else {
                    printf("INFO: Successfully opened asset file [%s]\n", asset_file_path.c_str());
                    std::string tdpath;
                    float fanimSpeed;
                    int fanimLen;
                    int tid;
                    while(fdata >> tdpath >> fanimSpeed >> fanimLen)
                    {
                        tid = tl->LoadTextureToList(tdpath);
                        this->addAnimation(tid, fanimSpeed, fanimLen);
                        printf("INFO: Loaded Animation from '%s' with TextureId [%d]\n", tdpath.c_str(), tid);
                    }
                    fdata.close();
                }
            }

            void updateAnimation(void)
            {
                if(animfCounter >= (FRAME_RATE/animSpeed.at(index)))
                {
                    animfCounter = 0;
                    if(animIndex < animLen.at(index))
                    {
                        animIndex++;
                    }
                    else
                    {
                        animIndex = 0;
                    }
                } else {
                    animfCounter++;
                }
            }

            Rectangle getAnimTextureCropPos(void)
            {
                Rectangle rect;
                rect = (Rectangle){
                    (float)animIndex, // Vector2 x top left corner of sprite
                    0.0f,                 // Vector2 y top left corner of sprite
                    1.0f,          // Vector2 x size (width)
                    1.0f,          // Vector2 y size (height)
                };
                return rect;
            }

    };

    class ObjectAnimation {
        public:
            int tId;

            void ObjecAnimation(void)
            {
                animIndex = 0;
                animSpeed = 1.0f;
                animLen = 1;
                animfCounter = 0;
            }

            void addAnimation(TextureList* tl, std::string path, float animationSpeed, int animationLen)
            {
                tId = tl->LoadTextureToList(path);
                animSpeed = animationSpeed;
                animLen = animationLen;
                printf("INFO: Added Object Animation\n");
            }

            void updateAnimation(void)
            {
                if(animfCounter >= (FRAME_RATE/animSpeed))
                {
                    animfCounter = 0;
                    if(animIndex < animLen)
                    {
                        animIndex++;
                    }
                    else
                    {
                        animIndex = 0;
                    }
                } else {
                    animfCounter++;
                }
            }

            Rectangle getAnimTextureCropPos(void)
            {
                Rectangle rect;
                rect = (Rectangle){
                    (float)animIndex,
                    0.0f,
                    1.0f,
                    1.0f
                };
                return rect;
            }


        private:
            int animIndex;
            float animSpeed;
            int animLen;
            int animfCounter;
    };
}

#endif
