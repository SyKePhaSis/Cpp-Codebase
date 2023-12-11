#pragma once
#ifndef CAMERA_H
#define CAMERA_H

//INCLUDES
#include "../../Libraries/RayLib/include/raylib.h"

#include <cstdio>
#include <stdbool.h>

class CameraAdv {

    public:

        CameraAdv(void){
            cam = { 0 };
            cam.target = (Vector2){0.0f, 0.0f};
            cam.offset = (Vector2){0.0f, 0.0f};
            cam.zoom = 1.0f;
            cam.rotation = 0.0f;
        }

        CameraAdv(Vector2 target, Vector2 offset){
            cam = { 0 };
            cam.target = target;
            cam.offset = offset;
            cam.zoom = 1.0f;
            cam.rotation = 0.0f;
        }

        void SetCameraState(void)
        {
            follow = !follow;
        }

        void SetZoomState(void)
        {
            zoom = !zoom;
        }

        void SetTarget(Vector2 target)
        {
            cam.target = target;
        }

        void SetOffset(Vector2 offset)
        {
            cam.offset = offset;
        }

        void UpdateCameraFollow(Vector2 *pos, Vector2 winDimentions)
        {
            if(!follow)
            {
                printf("ERROR: Camera is not set to follow mode\n");
                exit(-1);
            }
            cam.target.x = pos->x;
            cam.target.y = pos->y;
            cam.offset.x = winDimentions.x/2.0f;
            cam.offset.y = winDimentions.y/2.0f;
        }

        void UpdateCameraStatic()
        {
            if(zoom)
            {
                checkZoom();
            }
        }

    private:
        Camera2D cam;
        bool follow;
        bool zoom;

        void checkZoom(void)
        {
            cam.zoom += ((float)GetMouseWheelMove()*0.05f);
            if (cam.zoom > 3.0f)
            {
                cam.zoom = 3.0f;
            } else if (cam.zoom < 0.1f)
            {
                cam.zoom = 0.1f;
            }
        }
};

#endif
