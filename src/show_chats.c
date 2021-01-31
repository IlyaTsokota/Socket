#include "chat.h"

void show_chats(GtkWidget *main_grid)
{
    GtkBuilder *builder = glade_file_to_interface("share/chats.glade");
    main_form.left_content = GTK_WIDGET(gtk_builder_get_object(builder, "grid_contacts"));
    GtkWidget *contacts_panel = GTK_WIDGET(gtk_builder_get_object(builder, "contacts_panel"));
    main_form.chats_grid = GTK_WIDGET(gtk_builder_get_object(builder, "contacts_container"));
    gtk_grid_attach(GTK_GRID(main_grid), main_form.left_content, 0, 0, 1, 1);
    GtkWidget *arr[] = {main_form.left_content, contacts_panel,  main_form.chats_grid, NULL};                   
    css_set(arr, "share/resources/css/main.css");
    get_chats_from_db(main_form.chats_grid, data.user_id);
    g_object_unref(builder);
}
