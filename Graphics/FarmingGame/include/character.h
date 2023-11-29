#ifndef CHARACTER_H
#define CHARACTER_H

#include <stdio.h>
#include "../../../Libraries/RayLib/include/raylib.h"
#include "../../Sprite.h"

//DEFINING STRUCTS


//DEFINING FUNCTIONS
int initCharacter(const char* load_path, Vector2 spawn_point, SpriteList* sl_p);
int loadCharacter(const char* load_path, SpriteList* sl_p);
void checkMovement(Sprite *csp);
void updateCharacter(SpriteList *sl_p, Sprite* csp);
void setCharacterPos(SpriteList *sl_p, int charId, Vector2 vec);

#endif
