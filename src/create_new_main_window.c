#include "chat.h"
void create_new_main_window(GtkWidget **restrict window, char *window_id, char *path_to_window)
{
    GtkBuilder *builder = glade_file_to_interface(path_to_window);
    GtkWidget *new_window = GTK_WIDGET(gtk_builder_get_object(builder, window_id));
    g_signal_connect(new_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    css_set_for_one(new_window, "share/resources/css/auth.css");
    *window = new_window;
}
