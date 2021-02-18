#include "chat.h"

void show_chats(GtkWidget *main_grid)
{
    if (!do_once.bshow_chats)
        return;
    do_once.bshow_chats = false;
    GtkBuilder *builder = glade_file_to_interface(localization_s.chats);
    GtkWidget *child = GTK_WIDGET(gtk_builder_get_object(builder, "grid_contacts"));
    GtkWidget *contacts_panel = GTK_WIDGET(gtk_builder_get_object(builder, "contacts_panel"));
    main_form.chats_grid = GTK_WIDGET(gtk_builder_get_object(builder, "contacts_container"));

    show_chats_widgets();

    gtk_grid_attach(GTK_GRID(main_form.left_content[0]), child, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(main_grid), main_form.left_content[0], 0, 0, 1, 1);
    GtkWidget *arr[] = {main_form.left_content[0], contacts_panel, main_form.chats_grid, NULL};
    css_set(arr, data.main_theme_path);
    gtk_widget_show_all(main_form.left_content[0]);
    g_object_unref(builder);
}

void show_chats_widgets()
{
    if (chats_f.chat_items != NULL && chats_f.chat_items[0] != NULL)
    {
        for (int i = 0; chats_f.chat_items[i]; i++)
        {
            gtk_grid_attach(GTK_GRID(main_form.chats_grid), chats_f.chat_items[i]->event_box_contact, 0, i, 1, 1);
        }
    }
    gtk_widget_show_all(main_form.chats_grid);
}