#include "include/character.h"
#include "../Sprite.h"

// INITIALIZE CHARCTER
int loadCharacter(const char* load_path, SpriteList* sl_p)
{
    Image character = LoadImage(load_path);
    Sprite cs = SpriteInit(character);
    insertItem(sl_p, cs);
    return cs.id;
}


int InitCharacter(const char* load_path, Vector2 spawn_point, SpriteList* sl_p)
{
    int sid = loadCharacter(load_path, sl_p);
    setCharacterPos(sl_p, sid ,spawn_point);
    renderSprite(sl_p, sid);
    return sid;
}

//HELPER FUNCTIONS
void setCharacterPos(SpriteList *sl_p, int charId, Vector2 vec)
{
    setVec(sl_p, vec, charId);
}

//GAMELOOP FUNCTIONS FOR CHARACTER
void checkMovement(Sprite *csp)
{
    if(IsKeyDown(KEY_W))
    {
        csp->pos.y -= 50.0f * GetFrameTime();
    }
    if(IsKeyDown(KEY_A))
    {
        csp->pos.x -= 50.0f * GetFrameTime();
    }
    if(IsKeyDown(KEY_S))
    {
        csp->pos.y += 50.0f * GetFrameTime();
    }
    if(IsKeyDown(KEY_D))
    {
        csp->pos.x += 50.0f * GetFrameTime();
    }
}

void updateCharacter(SpriteList *sl_p, Sprite* csp)
{
    renderSprite(sl_p,csp->id);
    checkMovement(csp);
}
