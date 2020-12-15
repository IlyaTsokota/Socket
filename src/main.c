#include "chat.h"

// int main(int argc, char *argv[])
// {
//     gtk_init(&argc, &argv);
    // GtkWidget *authWindow;
    // create_new_main_window(&authWindow, "windowAuth", "share/window_auth.glade");
    // open_login(authWindow);
//     gtk_widget_show(authWindow);
//     gtk_main();
//     return 0;
// }

void application_activate(GtkApplication *application, gpointer user_data)
{
    GtkBuilder *builder = glade_file_to_interface("share/window_auth.glade");
    data.win= GTK_WIDGET(gtk_builder_get_object(builder, "windowAuth"));
    css_set_for_one(data.win, "share/resources/css/auth.css");
    open_login(data.win);
    gtk_application_add_window(data.app,GTK_WINDOW(data.win));
	gtk_widget_show_all(data.win);
}
void application_shutdown(GtkApplication *application, gpointer user_data)
{
	 g_application_quit(G_APPLICATION(data.app));
}

int main (int argc, char *argv[])
{	
	gtk_init (&argc, &argv);
	gint res;
	data.app = gtk_application_new("gtk.org", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(data.app, "activate", G_CALLBACK(application_activate), NULL);
	g_signal_connect(data.app, "shutdown", G_CALLBACK(application_shutdown), NULL);
	res = g_application_run(G_APPLICATION(data.app), 0, NULL);
    return 0;
}