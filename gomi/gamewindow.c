#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <X11/Xlib.h>

#include "gamewindow.h"

void gamewindow_init()
{
	XInitThreads();
	gtk_init(NULL,NULL);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	drawing_area = gtk_drawing_area_new();
	
	g_signal_connect(G_OBJECT(drawing_area),"draw",G_CALLBACK(draw_callback),NULL);
	g_signal_connect(G_OBJECT(window),"configure-event",G_CALLBACK(configure_event_callback),NULL);
	gtk_container_add(GTK_CONTAINER(window), drawing_area);

	gtk_window_set_default_size(GTK_WINDOW(window),300,500);
}

//for gdk_threads_add_timeout
gboolean call_function_without_argument(gpointer data)
{
	void(*fp)() = (void(*)()) data;
	fp();
	return G_SOURCE_CONTINUE;
}

//Raise draw event
gboolean on_draw(gpointer data)
{
	gamewindow_png_data*(*fp)() = (gamewindow_png_data*(*)())data;
	gamewindow_png_data* png = fp();	
	if(!png)
	{
		printf("?: png is null");
		return G_SOURCE_CONTINUE;
	}
	gamewindow_update_image(png->data,png->size);
	printf("%lu",png->size);
	gtk_widget_queue_draw(drawing_area);

	return G_SOURCE_CONTINUE;
}

gboolean draw_callback(GtkWidget *widget,cairo_t *cr,gpointer data)
{
	GdkRGBA color = {255,0,0,255};
	  cairo_arc (cr,
	               200 / 2.0, 299 / 2.0,
		                    MIN (200, 299) / 2.0,
				                 0, 2 * G_PI);
	gdk_cairo_set_source_rgba(cr,&color);
	cairo_fill(cr);

	if(!pixbuf)
	{
		return FALSE;
	}

	cairo_surface_t *surface = gdk_cairo_surface_create_from_pixbuf(pixbuf,1,NULL);
	cairo_set_source_surface(cr,surface,0,0);
	cairo_paint(cr);

	//free surface
	cairo_surface_destroy(surface);

	return FALSE;
}

void gamewindow_set_event_windowconfigurationchanged_callback(void(*fp)(int,int,int,int))
{
	gamewindow_event_windowconfigurationchanged_callback = fp;
}

gboolean configure_event_callback(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	GdkEventConfigure *configure = (GdkEventConfigure*)event;
	if(gamewindow_event_windowconfigurationchanged_callback)
	{
		gamewindow_event_windowconfigurationchanged_callback
		(configure->x,configure->y,
		configure->width,configure->height);
	}
	return FALSE;
}

void gamewindow_show()
{
	gtk_widget_show_all(window);
	gtk_widget_queue_draw(drawing_area);
}

void gamewindow_update_image(const unsigned char* image,unsigned long size)
{
	GdkPixbufLoader* loader = gdk_pixbuf_loader_new();
	gdk_pixbuf_loader_write(loader,image,size,NULL);

	pixbuf = gdk_pixbuf_loader_get_pixbuf(loader);
	gtk_widget_queue_draw(drawing_area);
	gdk_pixbuf_loader_close(loader,NULL);


}

void gamewindow_main()
{
	gtk_main();
}

void gamewindow_close()
{
	gtk_main_quit();
}

void gamewindow_set_event_windowclosing_callback(void(*fp)())
{
	g_signal_connect(window,"delete_event",G_CALLBACK(fp),NULL);
}

void gamewindow_set_event_gametick_callback(void(*fp)())
{
	gdk_threads_add_timeout(
	gametick_interval,
	call_function_without_argument,
	(gpointer)fp);
}

void gamewindow_set_event_draw_callback(gamewindow_png_data*(*fp)())
{
	gdk_threads_add_timeout(
	draw_interval,
	on_draw,
	(gpointer)fp);
}

const char* gamewindow_get_title()
{
	return gtk_window_get_title(GTK_WINDOW(window));
}

void gamewindow_set_title(const char *title)
{
	gtk_window_set_title(GTK_WINDOW(window),title);
}
