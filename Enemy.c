#include "Enemy.h"
#include <stdlib.h>

Enemy* Enemy_New()
{
	static cairo_surface_t* batsu_png = NULL;
	if(!batsu_png){
		batsu_png = cairo_image_surface_create_from_png
		("batsu.png");
	}
	Enemy* ret = malloc(sizeof(Enemy));
	ret->PNGImage = batsu_png;
	ret->Scale = 1.0;
	ret->Position = (Point){0,0};
	ret->Velocity = (Velocity){0,0};
	ret->HP = 1;
	ret->TouchDamage = 4;
	ret->DestroyScore = 100;
	ret->Dispose = Enemy_Dispose;
	return ret;
}

void Enemy_Dispose(Enemy* this)
{
	free(this);
}
