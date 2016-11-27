GtkWidget* window;
GtkWidget* drawing_area;

/* functions */
int main();

/* event callbacks */
void delete_event_callback();
gboolean draw_event_callback(GtkWidget* widget, cairo_t *cr, gpointer data);
