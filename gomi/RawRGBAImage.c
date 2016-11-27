
#include "RawRGBAImage.h"
#include <math.h>
#include <cairo/cairo.h>
#include <stdlib.h>
//Converts RawRGBAImage to cairo_surface_t
cairo_surface_t* RawRGBAImage2CairoSurface(RawRGBAImage *rawimage)
{

	cairo_surface_t* surface = 
	cairo_image_surface_create(CAIRO_FORMAT_ARGB32,rawimage->width,rawimage->height);

	cairo_t* ct = cairo_create(surface);
	int x,y;
	int offset = 0;
	for(x = 0; x < rawimage->width; x++)
	{
		for(y = 0; y < rawimage->height; y++)
		{
			unsigned char r,g,b,a;
			r = rawimage->data[offset + 0];
			g = rawimage->data[offset + 1];
			b = rawimage->data[offset + 2];
			a = rawimage->data[offset + 3];

			cairo_set_source_rgba(ct,r/255,g/255,b/255,a/255);
			cairo_rectangle(ct, x, y, 1, 1);
			cairo_fill(ct);
			offset += 4;
		}
	}
	cairo_set_source_rgba(ct,0.5,0.5,0.5,0.5);
	//cairo_rectangle(ct,0,0,222,222);
	//cairo_fill(ct);
	cairo_surface_flush(surface);
	cairo_destroy(ct);

	return surface;

}

RawRGBAImage* CairoSurface2RawRGBAImage(cairo_surface_t* surface)
{
	unsigned char* data = cairo_image_surface_get_data(surface);

	int width = cairo_image_surface_get_width(surface);
	int height = cairo_image_surface_get_height(surface);

	RawRGBAImage* rawimage = malloc(sizeof(RawRGBAImage));
	rawimage->data = malloc(4 * width * height); //4 bytes for each pixel
	rawimage->width = width;
	rawimage->height = height;

	int x,y;
	int offset = 0;
	for(x = 0; x < width; x++)
	{
		for(y = 0; y < height; y++)
		{
			unsigned char a,r,g,b;
			a = data[offset + 0];
			r = data[offset + 1];
			g = data[offset + 2];
			b = data[offset + 3];

			rawimage->data[offset + 0] = (unsigned char)(r / (a / 255));
			rawimage->data[offset + 1] = (unsigned char)(g / (a / 255));
			rawimage->data[offset + 2] = (unsigned char)(b / (a / 255));
			rawimage->data[offset + 3] = a;

			offset += 4;
		}
	}
	return rawimage;
}
