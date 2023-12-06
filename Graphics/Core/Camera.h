#pragnma once
#ifndef CAMERA_H
#define CAMERA_H

//INCLUDES
#include "../../Libraries/RayLib/include/raylib.h"

#include <stdio.h>
#include <stdbool.h>

//FUNCTION DECLARATIONS
Camera2D initCamera(Vector2 target, Vector2 offset);
void zoomFunction2D(Camera2D *cam);
void updateCameraStatic(Camera2D *cam, bool zoom);
void updateCameraFollow(Camera2D *cam, Vector2* pos,Vector2 winDimentions);

//FUNCTION IMPLEMENTATIONS
Camera2D initCamera2D(Vector2 target, Vector2 offset)
{
    Camera2D camera = { 0 };
    camera.target = target;
    camera.offset = offset;
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    return camera;
}

void zoomFunction2D(Camera2D *cam)
{
    cam->zoom += ((float)GetMouseWheelMove()*0.05f);
    if (cam->zoom > 3.0f)
    {
        cam->zoom = 3.0f;
    } else if (cam->zoom < 0.1f)
    {
        cam->zoom = 0.1f;
    }
}

void updateCameraStatic(Camera2D *cam, bool zoom)
{
    if(zoom)
    {
        zoomFunction2D(cam);
    }
}

void updateCameraFollow(Camera2D *cam, Vector2 *pos,Vector2 winDimentions)
{
    cam->target.x = pos->x;
    cam->target.y = pos->y;
    cam->offset.x = winDimentions.x/2.0f;
    cam->offset.y = winDimentions.y/2.0f;
    zoomFunction2D(cam);
}

#endif
