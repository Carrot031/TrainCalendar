#pragma once
#include "GameScene.h"
GtkWidget* window;
GtkWidget* drawing_area;
GameScene* game_scene = NULL;
GameScene* next_game_scene = NULL;

/* setup functions */
void setup_fonts();

/* processing interval */
const guint gametick_interval = 8;
const guint drawing_interval = 17;

/* aspect ratio */
const double aspect_ratio = 1.3333333333333;

/* timer event callbacks */
gboolean gametick_callback(gpointer);
gboolean drawing_callback(gpointer);

/* event callbacks */
gboolean delete_event_callback(GtkWidget*,GdkEventAny*);
gboolean draw_event_callback(GtkWidget* widget,cairo_t *cr, gpointer data);
gboolean key_press_event_callback(GtkWidget* widget,GdkEvent *event, gpointer user_data);
gboolean key_release_event_callback(GtkWidget* widget,GdkEventKey *event);
