#include "chat.h"

void show_opened_chat(GtkWidget *main_grid, char *chat_id)
{

    GtkBuilder *builder = glade_file_to_interface("share/opened_chat.glade");

    GtkWidget *child = GTK_WIDGET(gtk_builder_get_object(builder, "grid_message")); // это грид который буду менять
    GtkWidget *message_panel = GTK_WIDGET(gtk_builder_get_object(builder, "message_panel"));
    GtkWidget *messages_container = GTK_WIDGET(gtk_builder_get_object(builder, "messages_container"));
    main_form.message_line = GTK_WIDGET(gtk_builder_get_object(builder, "message_line"));
    main_form.message_scroll = GTK_WIDGET(gtk_builder_get_object(builder, "message_scroll"));

    if (curr_chat.messages_g != NULL)
    {
        int j = 0;
        for (int i = 0; curr_chat.messages_g[i]; i++)
        {
            char *curr_id = (char *)gtk_widget_get_name(curr_chat.messages_g[i]->message);
          
            if (strcmp(chat_id, curr_id) == 0)
            {
                gtk_grid_attach(GTK_GRID(main_form.message_line), curr_chat.messages_g[i]->event_box_message, 0, j++, 1, 1);
            }
        }
    }
    gtk_widget_show_all(main_form.message_line);

    //memory leak
    msg_t *msg_entry = (msg_t *)malloc(sizeof(msg_t));
    GtkWidget *message_size_body = GTK_WIDGET(gtk_builder_get_object(builder, "message_size_body"));
    msg_entry->text_view = GTK_WIDGET(gtk_builder_get_object(builder, "message_input"));
    msg_entry->buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(msg_entry->text_view));
    msg_entry->container = GTK_WIDGET(gtk_builder_get_object(builder, "message_input_scroll"));
    // char *placeholder_msg = "Write a message...";
    main_form.text_view = msg_entry->text_view;
    // g_signal_connect(G_OBJECT(message_input), "focus-in-event", G_CALLBACK(change_placeholder_msg_in_focus), placeholder_msg);
    // g_signal_connect(G_OBJECT(message_input), "focus-out-event", G_CALLBACK(change_placeholder_msg_out_focus), placeholder_msg);
    GtkWidget *emoji_container = GTK_WIDGET(gtk_builder_get_object(builder, "emoji_container"));
    GtkWidget *event_box_emoji = GTK_WIDGET(gtk_builder_get_object(builder, "event_box_emoji"));
    GtkWidget *pin_container = GTK_WIDGET(gtk_builder_get_object(builder, "pin_container"));
    GtkWidget *event_box_pin = GTK_WIDGET(gtk_builder_get_object(builder, "event_box_pin"));
    g_signal_connect(G_OBJECT(event_box_pin), "button-press-event", G_CALLBACK(send_pinned_resource), NULL);
    GtkWidget *send_container = GTK_WIDGET(gtk_builder_get_object(builder, "send_container"));
    GtkWidget *event_box_send = GTK_WIDGET(gtk_builder_get_object(builder, "event_box_send"));

    g_signal_connect(G_OBJECT(event_box_send), "button-press-event", G_CALLBACK(send_message), msg_entry->text_view);
    g_signal_connect(G_OBJECT(event_box_emoji), "button-press-event", G_CALLBACK(show_emoji), msg_entry->text_view);
    g_signal_connect(G_OBJECT(msg_entry->buffer), "changed", G_CALLBACK(change_size_message_input), msg_entry);

    // g_signal_connect_after(G_OBJECT(msg_entry->buffer), "insert-text", G_CALLBACK(insert_text), NULL);

    GtkWidget *arr[] = {main_form.right_content[0], message_panel, messages_container, main_form.message_line, message_size_body,
                        msg_entry->text_view, msg_entry->container, main_form.message_scroll, emoji_container, event_box_emoji, pin_container, send_container, event_box_send, NULL};
    
    g_timeout_add(50, change_insert_to_message, main_form.message_scroll);
    css_set(arr, data.main_theme_path);

    gtk_grid_attach(GTK_GRID(main_form.right_content[0]), child, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content[0], 1, 0, 1, 1);
    gtk_widget_show_all(main_form.right_content[0]);

    g_object_unref(builder);
}
