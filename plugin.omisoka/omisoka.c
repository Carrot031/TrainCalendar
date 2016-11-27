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
	time_t omisoka_time;
	struct tm omisoka = {0};

	double diff = 0;

	time(&timer);

	strptime("2016/12/31","%Y/%m/%d",&omisoka);
	omisoka.tm_year = 2016-1900;
	omisoka.tm_mon = 11;
	omisoka_time = mktime(&omisoka);

	diff = difftime(omisoka_time,timer);
	cairo_set_source_rgb(cr,0.0,0.0,0.0);
	cairo_translate(cr,0.05*width,0.05*height);
	PangoLayout *layout;
	PangoFontDescription *desc;
	layout = pango_cairo_create_layout(cr);
	char msg[256];
	snprintf(msg,sizeof(msg),"大晦日まで%d日です。",(int)(diff/86400.0));
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
