#include "Chinatsu.h"
#include "cairo/cairo.h"
#include <stdlib.h>

Enemy* Chinatsu_New()
{
	static cairo_surface_t* chinatsu_png = NULL;
	if(!chinatsu_png){
		chinatsu_png = cairo_image_surface_create_from_png
		("chinatsu.png");
	}
	Enemy* ret = Enemy_New();
	ret->PNGImage = chinatsu_png;
	ret->Scale = 0.8;
	ret->Velocity = (Velocity){-1,0};
	return ret;
}

void Chinatsu_Dispose(Enemy* this)
{
	Enemy_Dispose(this);
}
