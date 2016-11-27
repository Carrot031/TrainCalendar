#include "cairo/cairo.h"
#include "pango/pangocairo.h"
#include <time.h>
int IsActive(){
	return 1;
}

int Draw(cairo_t* cr,int width,int height,int lwidth,int lheight)
{
	/*cairo_set_source_rgb(cr,0.0,0.0,1.0);
	cairo_rectangle(cr,0,0,width,height);
	cairo_fill(cr);*/

	time_t timer;
	struct tm tm_timer;
	int min = 0;

	time(&timer);
	tm_timer = *localtime(&timer);
	min = 1440 - tm_timer.tm_hour * 60 - tm_timer.tm_min;


	cairo_set_source_rgb(cr,0.0,0.0,0.0);
	cairo_translate(cr,0.05*width,0.05*height);
	PangoLayout *layout;
	PangoFontDescription *desc;
	layout = pango_cairo_create_layout(cr);
	char msg[256];
	snprintf(msg,sizeof(msg),"次の日まで%d分です。",min);
	pango_layout_set_text(layout, msg, -1);



	char fds[64];
	snprintf(fds,sizeof(fds),"IPAexGothic %dpx",(int)((double)0.07*width));
	desc = pango_font_description_from_string(fds);
	pango_layout_set_font_description(layout,desc);
	pango_font_description_free(desc);

	pango_cairo_update_layout(cr,layout);
	pango_cairo_show_layout(cr,layout);

	g_object_unref(layout);

	return 100;
}
