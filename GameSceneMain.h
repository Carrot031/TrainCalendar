#pragma once
#include "cairo/cairo.h"
#include "pango/pangocairo.h"
#include "SList.h"
#include "stdbool.h"
#include "Point.h"
#include "Akari.h"
#include "Enemy.h"
#include "Odango.h"
#include "TCPlugin.h"
#include "Config.h"
#include <dirent.h>
/* class members */
GameScene* GameSceneMain_New();
GameScene* GameSceneMain_GameTick(void*);
void GameSceneMain_KeyDown(void*,GameKeys);
void GameSceneMain_KeyUp(void*,GameKeys);
void GameSceneMain_Draw(void*,cairo_t*,int w,int h);
void GameSceneMain_CleanOdangoSList(void*);
void GameSceneMain_CleanOdangoArray(void*);
void GameSceneMain_Dispose(void*);

/* MenuItem */
/*
typedef struct _GameSceneMenu_MenuItem{
	const char* Name;
	void (*Behavior)(void*);
	struct _GameSceneMenu_MenuItem* Next;
} GameSceneMenu_MenuItem;
*/

/*
void GameSceneMenu_MenuItem_Continue_Behavior(void*);
void GameSceneMenu_MenuItem_Exit_Behavior(void*);
*/

typedef enum{
	Japanese,
	English
} Language;

/* field*/
typedef struct{
	/* SList* Menu; */
	/* images */
	/*
	cairo_surface_t* akari_png;
	cairo_surface_t* odango_png;
	cairo_surface_t* crying_akari_png;
	*/

	PangoFontDescription* pfd_menu;
	Akari* Akari;
	int CleanOdangoTick;
	Odango** OdangoArray;
	Enemy** EnemyArray;
	/* status */
	int Score;
	bool AttackFlag;
	bool KeyUpFlag;
	bool KeyDownFlag;
	bool KeyLeftFlag;
	bool KeyRightFlag;
	Language Language;
	int PluginIndex;

	/* alive */
	bool AliveFlag;
	/* int SelectionIndex; */
	int NTickAttackCount;
	int NTickLanguageCount;
	int NTickPluginCount;

	/* plugins */
	int NPlugins;
	void** PluginHandleArray;
	Draw* PluginFunctionArray;
	IsActive* PluginIsActiveArray;
} GameSceneMain_Field;
