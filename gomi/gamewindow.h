GtkWidget* window;
GtkWidget* drawing_area;
GdkPixbuf* pixbuf = NULL;
unsigned int gametick_interval = 8;
unsigned int draw_interval = 17;


typedef struct
{
	const unsigned char* data;
	unsigned long size;
} gamewindow_png_data;


/* internal event callbacks */
gboolean draw_callback(GtkWidget *widget,cairo_t *cr, gpointer data);
gboolean configure_event_callback(GtkWidget *widget,GdkEvent *event,gpointer data);

/* internal functions */
gboolean call_function_without_argument(gpointer fp);
gboolean on_draw(gpointer data);

/* outbound event callbacks */
void (*gamewindow_event_windowclosing_callback)() = NULL;
void gamewindow_set_event_windowclosing_callback(void(*)());

void (*gamewindow_event_gametick_callback)() = NULL;
void gamewindow_set_event_gametick_callback(void(*)());

void (*gamewindow_event_draw_callback)() = NULL;
void gamewindow_set_event_draw_callback(gamewindow_png_data*(*)());

void (*gamewindow_event_windowconfigurationchanged_callback)
(int x,int y,int width,int height) = NULL;
void gamewindow_set_event_windowconfigurationchanged_callback(void(*)(int,int,int,int));


void gamewindow_init();
void gamewindow_set_processing_interval(unsigned int interval);
void gamewindow_set_drawing_interval(unsigned int interval);
void gamewindow_main();
void gamewindow_update_image(const unsigned char*,unsigned long);
void gamewindow_show();
void gamewindow_close();


const char* gamewindow_get_title();
void gamewindow_set_title(const char*);
