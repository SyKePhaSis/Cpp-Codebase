#ifndef UICOMPONENTS_H
#define UICOMPONENTS_H

#include "../../Libraries/RayLib/include/raylib.h"
#include "TextureLoader.h"
#include "Camera.h"

#include <string.h>
#include <stdbool.h>

int UIid;

typedef struct {
    int id;
    Rectangle rect;
    int textId;
} UIComponent;

typedef struct {
    char name[64];
    int size;
    int capacity;
    UIComponent* uiarray;
} UIHolder;

UIHolder createUIHolder(const char* name)
{
    UIHolder uih;
    strcpy(uih.name, name);
    uih.size = 0;
    uih.capacity = MAX_UI_OBJECTS;
    uih.uiarray = malloc(uih.capacity * sizeof(UIComponent));
    if(uih.uiarray)
    {
        printf("INFO: UIHolder succesfully created and alocated [%lld] bytes\n", uih.capacity * sizeof(UIComponent));
    }
    return uih;
}

UIComponent createUIComponent(TextureList* tl, Vector2 pos, Vector2 size, const char* path)
{
    UIComponent b;
    b.id = UIid;
    UIid++;
    b.rect = (Rectangle){
        pos.x,
        pos.y,
        size.x,
        size.y
    };
    b.textId = LoadTextureTL(tl, path);
    return b;
}

void addUIComponent(UIHolder* uih, UIComponent uic)
{
    if(uih->size == uih->capacity)
    {
        printf("ERROR: Cannot add more UI elements to UIHolder\n");
    }
    else {
        uih->uiarray[uih->size++] = uic;
    }
}

void loadUIFromFile(UIHolder* uih, TextureList *tl , const char* path)
{
    FILE *fp = fopen(path, "r");
    if(!fp)
    {
        printf("ERROR: Couldn't open UI File [%s]\n", path);
    } else {
        char t_path[100];
        Vector2 pos;
        Vector2 size;
        while(fscanf(fp,"%s%f%f%f%f", t_path, &pos.x, &pos.y, &size.x, &size.y) == 5)
        {
            UIComponent uip = createUIComponent(tl, pos, size, t_path);
            addUIComponent(uih, uip);
            printf("INFO: Added UI Component from [%s]\n", path);
        }
    }
}

UIComponent* getUIComponentP(UIHolder* uihp, int id)
{
    return &uihp->uiarray[id];
}

void drawUIcomponent(Camera2D *cam, UIComponent* uic, TextureList *tl)
{
    Texture2D t = getTextureFromIdTL(tl, uic->textId);
    DrawTextureV(t, (Vector2){uic->rect.x,uic->rect.y}, WHITE);
}

void drawUIHolder(Camera2D* cam, UIHolder* uihp, TextureList *tl)
{
    for(int i = 0; i < uihp->size; i++)
    {
        UIComponent *uicp = getUIComponentP(uihp, i);
        drawUIcomponent(cam, uicp, tl);
    }
}

#endif
