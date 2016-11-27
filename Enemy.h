#pragma once
#include "Point.h"
#include "Velocity.h"
#include "cairo/cairo.h"
typedef struct _Enemy
{
	cairo_surface_t* PNGImage;
	double Scale;
	Point Position;
	Velocity Velocity;
	int HP;
	int TouchDamage;
	int DestroyScore;
	void (*Dispose)();
	void* Field;
} Enemy;

Enemy* Enemy_New();
void Enemy_Dispose(Enemy*);
