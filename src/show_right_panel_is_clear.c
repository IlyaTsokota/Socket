#include "chat.h"

void show_right_panel_is_clear(GtkWidget *main_grid)
{
    GtkBuilder *builder = glade_file_to_interface("share/right_clear.glade");
    main_form.right_content = GTK_WIDGET(gtk_builder_get_object(builder, "clear_right")); 
    css_set_for_one(main_form.right_content, "share/resources/css/main.css");
    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content, 1, 0, 1, 1);
    g_object_unref(builder);
}