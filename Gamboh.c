#include "Gamboh.h"

Enemy* Gamboh_New()
{
	Enemy* ret = Enemy_New();
	ret->Scale = 4.0;
	ret->Velocity = (Velocity){-1,0};
	return ret;
}

void Gamboh_Dispose(Enemy* this)
{
	Enemy_Dispose(this);
}
