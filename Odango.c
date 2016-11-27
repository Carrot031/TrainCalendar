#include "Odango.h"
#include <stdlib.h>

Odango* Odango_New()
{
	Odango* ret = malloc(sizeof(Odango));
	return ret;
}

void Odango_Dispose(Odango* this)
{
	free(this);
}
