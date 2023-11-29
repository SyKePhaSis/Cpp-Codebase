#include "../Window.h"
#include "../Sprite.h"
#include "../Tilemap.h"
#include "../../Libraries/RayLib/include/raylib.h"
#include "character.c"
#include <stdio.h>

#define FRAME_RATE 60
#define WIDTH 960
#define HEIGHT 600

int main(void)
{
    Window win = {.width = WIDTH, .height = HEIGHT, .title = "Test"};
    InitWin(win, FRAME_RATE);

    //LOAD MAP
    Map map = LoadMap("./assets/maps/map.png");

    //SPRITE MANAGER
    SpriteList  sl;
    SpriteList* sl_p = &sl;
    InitSpriteList(sl_p);

    //INIT CHARACTER

    // Image character = LoadImage("./assets/character/character.png");
    // Sprite char_sprite = SpriteInit(character);
    // Sprite *cps = &char_sprite;
    // insertItem(sl_p, cps);

    int sid = InitCharacter("./assets/character/character.png", (Vector2){WIDTH/2.0f, HEIGHT/2.0f}, sl_p);
    Sprite* sp = getItemP(sl_p, sid);

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(GRAY);
        DrawMap(&map);
        updateCharacter(sl_p, sp);
        EndDrawing();
    }

    printArray(sl_p);
    freeSpriteList(sl_p);

    CloseWindow();
    return 1;
}
