/* Chemimon main source code. */

#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "SDL_render.h"
#include "chemimon.h"
int chemimon_init()
{
	return 0;
}

void chemimon_gametick()
{
}

RawRGBAImage* chemimon_draw()
{

	int rmask = 0xff000000;
	int gmask = 0x00ff0000;
	int bmask = 0x0000ff00;
	int amask = 0x000000ff;

	SDL_Surface *surface 
	= SDL_CreateRGBSurface(0, 400, 400,32,rmask,gmask,bmask,amask);

	Draw_Line(surface,0,0,100,200,0x00ffffff);

	RawRGBAImage* img = malloc(sizeof(RawRGBAImage));
	img->width = 200;
	img->height = 200;
	img->data = malloc(4 * 200 * 200);
	img->data[0] = 255;
	img->data[1] = 0;
	img->data[2]= 0;
	img->data[3] = 255;
	return img;
}
