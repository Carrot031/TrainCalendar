#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <X11/Xlib.h>
#include "chemimon.h"
#include "chemimon_window.h"
#include "RawRGBAImage.h"
int main()
{
	XInitThreads();
	gtk_init(NULL,NULL);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	drawing_area = gtk_drawing_area_new();
	
	gtk_container_add(GTK_CONTAINER(window),drawing_area);

	gtk_widget_show_all(window);
	g_signal_connect
	(G_OBJECT(window),"delete-event",delete_event_callback,NULL);

	g_signal_connect
	(G_OBJECT(drawing_area),"draw",G_CALLBACK(draw_event_callback),NULL);

	chemimon_init();

	gtk_main();
	return 0;
}
void delete_event_callback()
{
	gtk_main_quit();
}

gboolean draw_event_callback(GtkWidget *widget,cairo_t *cr, gpointer data)
{
	GdkRGBA color = {0,0,255,255};
	gdk_cairo_set_source_rgba(cr, &color);
	cairo_rectangle(cr,0,0,255,255);
	cairo_fill(cr);
	
	RawRGBAImage* img = chemimon_draw();
	cairo_surface_t* surface = 
	RawRGBAImage2CairoSurface(img);
	
	cairo_set_source_surface(cr,surface,0,0);
	cairo_paint(cr);
	return FALSE;
}
