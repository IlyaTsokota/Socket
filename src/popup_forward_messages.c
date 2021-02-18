#include "chat.h"

gboolean on_popup_focus_out(GtkWidget *widget, GdkEventFocus *event, gpointer data)
{
    free_chat_widgets(chats_form_sec.chat_items);

    gtk_widget_destroy(widget);
    return TRUE;
}

void on_popup_clicked(GtkMenuItem *menuitem, gpointer user_data)
{

    main_form.popup_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(main_form.popup_window), "Pop Up window");
    gtk_container_set_border_width(GTK_CONTAINER(main_form.popup_window), 10);
    gtk_window_set_resizable(GTK_WINDOW(main_form.popup_window), FALSE);
    gtk_window_set_decorated(GTK_WINDOW(main_form.popup_window), FALSE);
    gtk_window_set_skip_taskbar_hint(GTK_WINDOW(main_form.popup_window), TRUE);
    gtk_window_set_skip_pager_hint(GTK_WINDOW(main_form.popup_window), TRUE);
    gtk_widget_set_size_request(main_form.popup_window, -1, 600);
    gtk_window_set_transient_for(GTK_WINDOW(main_form.popup_window), GTK_WINDOW(data.win));
    gtk_window_set_position(GTK_WINDOW(main_form.popup_window), GTK_WIN_POS_CENTER);

    gtk_widget_set_events(main_form.popup_window, GDK_FOCUS_CHANGE_MASK);
    g_signal_connect(G_OBJECT(main_form.popup_window),
                     "focus-out-event",
                     G_CALLBACK(on_popup_focus_out),
                     NULL);

    GtkBuilder *builder = glade_file_to_interface("share/forward.glade");
    GtkWidget *child = GTK_WIDGET(gtk_builder_get_object(builder, "grid_contacts"));
    GtkWidget *contacts_panel = GTK_WIDGET(gtk_builder_get_object(builder, "contacts_panel"));
    GtkWidget *chats_grid = GTK_WIDGET(gtk_builder_get_object(builder, "contacts_container"));

    chat_t **chats = take_chats(data.user_id, data.socket_desc);
    if (chats != NULL)
    {
        chats_f.was_free = false;
        int size = 0;
        for (size_t i = 0; chats[i]; i++)
        {
            size++;
        }
        sort_chats(chats, size);
        for (size_t i = 0; i < size; i++)
        {
            create_one_forward_chat(i, chats[i]);
        }
        free_chats(chats);
    }

    if (chats_form_sec.chat_items != NULL && chats_form_sec.chat_items[0] != NULL)
    {
        for (int i = 0; chats_form_sec.chat_items[i]; i++)
        {
            gtk_grid_attach(GTK_GRID(chats_grid), chats_form_sec.chat_items[i]->event_box_contact, 0, i, 1, 1);
        }
    }
    gtk_widget_show_all(chats_grid);

    gtk_container_add(GTK_CONTAINER(main_form.popup_window), child);

    GtkWidget *arr[] = {child, contacts_panel, chats_grid, NULL};
    css_set(arr, data.main_theme_path);
    g_object_unref(builder);

    gtk_widget_show_all(main_form.popup_window);
    gtk_widget_grab_focus(main_form.popup_window);
}