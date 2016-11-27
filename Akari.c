#include <stdlib.h>
#include "Akari.h"

Akari* Akari_New()
{
	Akari* ret = malloc(sizeof(Akari));
	ret->HP = 100;
	ret->Level = 1;
	ret->Lives = 4;
	ret->TouchDamage = 2;
	return ret;
}

void Akari_Destroy(Akari* this)
{
	free(this);
}
