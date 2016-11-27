#pragma once
#include "cairo/cairo.h"
#include "GameKeys.h"
typedef struct _GameScene{
	struct _GameScene* (*GameTick)(void*);
	void(*Draw)(void*,cairo_t*,int w,int h);
	void(*KeyDown)(void*,GameKeys);
	void(*KeyUp)(void*,GameKeys);
	void(*Dispose)(void*);
	void* Field; /* subclass-specified data */
} GameScene;
