/* Chemimon main source code. */

#include <stdio.h>
#include <stdlib.h>
#include "gtk/gtk.h"
#include "X11/Xlib.h"
#include <pango/pangocairo.h>
#include <fontconfig/fontconfig.h>
#include "OdangoShooting.h"
#include "GameSceneMenu.h"


int main()
{
	setup_fonts();
	//XInitThreads();
	gtk_init(NULL,NULL);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"TrainCalendar");
	gtk_window_set_default_size(GTK_WINDOW(window),400,300);

	drawing_area = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER(window),drawing_area);

	//set event callbacks
	g_signal_connect(window,"delete-event",G_CALLBACK(delete_event_callback),
	NULL);
	g_signal_connect(window,"key-press-event",G_CALLBACK(key_press_event_callback),
	NULL);
	g_signal_connect(window,"key-release-event",G_CALLBACK(key_release_event_callback),
	NULL);
	g_signal_connect(drawing_area,"draw",G_CALLBACK(draw_event_callback),NULL);

	gdk_threads_add_timeout(gametick_interval,gametick_callback,NULL);
	gdk_threads_add_timeout(17,drawing_callback,NULL);

	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}

gboolean gametick_callback(gpointer user_data)
{
	if(!game_scene)
	{
		next_game_scene = GameSceneMenu_New();
	}

	if(next_game_scene)
	{
		if(game_scene)
		{
			game_scene->Dispose(game_scene);
		}
		game_scene = next_game_scene;
		next_game_scene = NULL;
	}

	next_game_scene = game_scene->GameTick(game_scene);
	return G_SOURCE_CONTINUE;
}

gboolean drawing_callback(gpointer user_data)
{
	gtk_widget_queue_draw(drawing_area);
	return G_SOURCE_CONTINUE;
}

gboolean delete_event_callback(GtkWidget *widget,GdkEventAny *event)
{
	gtk_main_quit();
	return FALSE;
}

gboolean key_press_event_callback(GtkWidget* widget,GdkEvent* event,gpointer data)
{
	switch(((GdkEventKey*)(event))->keyval)
	{
		case GDK_KEY_Return:
			game_scene->KeyDown(game_scene,GameKey_A);
			break;
		case GDK_KEY_Up:
			game_scene->KeyDown(game_scene,GameKey_Up);
			break;
		case GDK_KEY_Down:
			game_scene->KeyDown(game_scene,GameKey_Down);
			break;
		case GDK_KEY_Left:
			game_scene->KeyDown(game_scene,GameKey_Left);
			break;
		case GDK_KEY_Right:
			game_scene->KeyDown(game_scene,GameKey_Right);
			break;
	}
	return FALSE;
}

gboolean key_release_event_callback(GtkWidget *widget,GdkEventKey *event)
{
	if(!game_scene->KeyUp){
		return FALSE;
	}
	switch(event->keyval)
	{
		case GDK_KEY_Return:
			game_scene->KeyUp(game_scene,GameKey_A);
			break;
		case GDK_KEY_Up:
			game_scene->KeyUp(game_scene,GameKey_Up);
			break;
		case GDK_KEY_Down:
			game_scene->KeyUp(game_scene,GameKey_Down);
			break;
		case GDK_KEY_Left:
			game_scene->KeyUp(game_scene,GameKey_Left);
			break;
		case GDK_KEY_Right:
			game_scene->KeyUp(game_scene,GameKey_Right);
			break;
	}
	return FALSE;
}

gboolean draw_event_callback(GtkWidget* widget, cairo_t* cr,gpointer data)
{
	guint width = gtk_widget_get_allocated_width(widget);
	guint height = gtk_widget_get_allocated_height(widget);
	guint fixed_width = width;
	guint fixed_height = height;

	double ratio = (double)width / (double)height;
	if(ratio > aspect_ratio)
	{
		fixed_width = (guint)(height * aspect_ratio);
	}else{
		fixed_height = (guint)(width / aspect_ratio);
	}

	if(game_scene)
	{
		game_scene->Draw(game_scene,cr,fixed_width,fixed_height);
	}
	return FALSE;
}

void setup_fonts()
{
	const FcChar8* file = (FcChar8*)"fonts/ipaexg00301/ipaexg.ttf";
	FcBool fontAddStatus = FcConfigAppFontAddFile(NULL,file);
	if(fontAddStatus == FcTrue)
	{
		printf("IPA font has successfully loaded.\n");
	}
}

