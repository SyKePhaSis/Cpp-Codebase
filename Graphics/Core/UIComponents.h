#pragma once
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
    bool show;
} UIComponent;

typedef struct {
    char name[64];
    int size;
    int capacity;
    UIComponent* uiarray;
    bool show;
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

UIComponent createUIComponent(TextureList* tl, Vector2 pos, Vector2 size, const char* path, int show)
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
    b.show = show;
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
        printf("INFO: Succesfully added element to UIHolder\n");
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
        int show;
        while(fscanf(fp,"%s%f%f%f%f%d", t_path, &pos.x, &pos.y, &size.x, &size.y, &show) == 6)
        {
            UIComponent uip = createUIComponent(tl, pos, size, t_path, show);
            addUIComponent(uih, uip);
            printf("INFO: Added UI Component from [%s]\n", path);
        }
    }
}

void drawUIText(UIComponent* uic, const char* text)
{
    if(uic->show)
    {
        // Font font = LoadFont("../assets/fonts/pixelify.ttf");
        Font font = GetFontDefault();
        DrawTextEx(font, text, (Vector2){uic->rect.x, uic->rect.y}, 20.0f, 1.0f, WHITE);
    }
}

UIComponent* getUIComponentP(UIHolder* uihp, int id)
{
    return &uihp->uiarray[id];
}

void drawUIcomponent(UIComponent* uic, TextureList *tl)
{
    if(uic->show)
    {
        Texture2D t = getTextureFromIdTL(tl, uic->textId);
        DrawTextureV(t, (Vector2){uic->rect.x,uic->rect.y}, WHITE);
    }
}

void drawUIHolder(UIHolder* uihp, TextureList *tl)
{
    if(uihp->show)
    {
        for(int i = 0; i < uihp->size; i++)
        {
            UIComponent *uicp = getUIComponentP(uihp, i);
            drawUIcomponent(uicp, tl);
            if(DEBUG)
            {
                DrawRectangleLinesEx(uicp->rect, 1.0f, RAYWHITE);
            }
        }
    }
}

#endif
