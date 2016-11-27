#pragma once
#include "Point.h"
#include "Velocity.h"
typedef struct{
	Velocity Velocity;
	Point Position;
} Odango;

Odango* Odango_New();
void Odango_Dispose(Odango*);
