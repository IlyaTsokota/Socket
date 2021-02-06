#include "chat.h"

void show_chats(GtkWidget *main_grid)
{
    static bool do_once = true;
    if (!do_once)
        return;
    GtkBuilder *builder = glade_file_to_interface("share/chats.glade");
    GtkWidget *child = GTK_WIDGET(gtk_builder_get_object(builder, "grid_contacts"));
    GtkWidget *contacts_panel = GTK_WIDGET(gtk_builder_get_object(builder, "contacts_panel"));
    main_form.chats_grid = GTK_WIDGET(gtk_builder_get_object(builder, "contacts_container"));
    GtkWidget *arr[] = {main_form.left_content[0], contacts_panel, main_form.chats_grid, NULL};
    css_set(arr, "share/resources/css/main.css");
    for (int i = 0; chats_f.chat_items[i]; i++)
    {
        gtk_grid_attach(GTK_GRID(main_form.chats_grid), chats_f.chat_items[i]->event_box_contact, 0, i, 1, 1);
    }
    gtk_grid_attach(GTK_GRID(main_form.left_content[0]), child, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(main_grid), main_form.left_content[0], 0, 0, 1, 1);
    gtk_widget_show_all(main_form.left_content[0]);
    do_once = false;
    g_object_unref(builder);
}