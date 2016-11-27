#pragma once
#include "cairo/cairo.h"
#include "RawRGBAImage.h"
typedef struct
{
	unsigned char *data;
	int width;
	int height;
} RawRGBAImage;

cairo_surface_t* RawRGBAImage2CairoSurface(RawRGBAImage*);
