#pragma once
#include "Point.h"

typedef struct _Akari{
	int HP;
	int Level;
	int Lives;
	int TouchDamage;
	Point Position;
} Akari;

Akari* Akari_New();
void Akari_Dispose(Akari*);
