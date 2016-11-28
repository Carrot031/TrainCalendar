#pragma once
#include <stdbool.h>
#include "cairo/cairo.h"
#include "pango/pangocairo.h"
#include "SList.h"
#include "GameSceneMain.h"
/* class members */
GameScene* GameSceneMenu_New();
GameScene* GameSceneMenu_GameTick(void*);
void GameSceneMenu_KeyDown(void*,GameKeys);
void GameSceneMenu_Draw(void*,cairo_t*,int w,int h);
void GameSceneMenu_Dispose(void*);

/* MenuItem */
typedef struct _GameSceneMenu_MenuItem{
	const char* Name;
	void (*Behavior)(void*);
	struct _GameSceneMenu_MenuItem* Next;
} GameSceneMenu_MenuItem;

void GameSceneMenu_MenuItem_Start_Behavior(void*);
void GameSceneMenu_MenuItem_Exit_Behavior(void*);
/* field*/
typedef struct{
	SList* Menu;
	//cairo_surface_t* logo_png;
	PangoFontDescription* pfd_menu;
	bool StartFlag;
	int SelectionIndex;
} GameSceneMenu_Field;
