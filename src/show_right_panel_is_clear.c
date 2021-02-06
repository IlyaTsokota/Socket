#include "chat.h"

void show_right_panel_is_clear(GtkWidget *main_grid)
{
      static bool do_once = true;
    if (!do_once)
        return;
    GtkBuilder *builder = glade_file_to_interface("share/right_clear.glade");
    GtkWidget *child = GTK_WIDGET(gtk_builder_get_object(builder, "clear_right")); 
    css_set_for_one(main_form.right_content[1], "share/resources/css/main.css");
           gtk_grid_attach(GTK_GRID(main_form.right_content[1]), child, 0, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content[1], 1, 0, 1, 1);
            gtk_widget_show_all(main_form.right_content[1]);

    g_object_unref(builder);
    do_once = false;
}