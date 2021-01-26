#include "chat.h"

void get_messages_for_current_chat_from_db(GtkWidget *container_msg)
{
    message_t **message = get_messages_from_file("messages.json", "3");

    puts("-----------------------");
    puts(message[1]->ms_text);
    puts("-----------------------");

    // if (message != NULL)
    // {
    //     int size = 0;
    //     for (size_t i = 0; message[i]; i++)
    //     {
    //         size++;
    //     }
    //     messages_t **messages_g = (messages_t **)malloc(sizeof(messages_t *) * (size + 1));
    //     messages_g[size] = NULL;

    //     for (size_t i = 0; i < size; i++)
    //     {
    //         messages_g[i] = (messages_t *)malloc(sizeof(messages_t));
    //         messages_g[i]->event_box_message = gtk_event_box_new();
    //         // g_signal_connect(G_OBJECT(chats_f.chat_items[i]->event_box_contact), "button-press-event", G_CALLBACK(open_click_chat), NULL);
    //         gtk_widget_set_hexpand(messages_g[i]->event_box_message, true);
    //         gtk_widget_set_halign(messages_g[i]->event_box_message, GTK_ALIGN_START);
    //         gtk_widget_set_vexpand(messages_g[i]->event_box_message, true);
    //         gtk_widget_set_name(messages_g[i]->event_box_message, message[i]->ms_id);

    //         messages_g[i]->message = gtk_grid_new();
    //         gtk_widget_set_hexpand(messages_g[i]->message, true);
    //         gtk_widget_set_vexpand(messages_g[i]->message, true);
    //         set_style_context(messages_g[i]->message, "message-body");

    //         messages_g[i]->message_info = gtk_grid_new();
    //         gtk_widget_set_hexpand(messages_g[i]->message_info, true);
    //         gtk_widget_set_vexpand(messages_g[i]->message_info, true);
    //         gtk_widget_set_halign(messages_g[i]->message_info, GTK_ALIGN_START);

    //         messages_g[i]->message_time = gtk_label_new(message[i]->ms_datetime);
    //         gtk_widget_set_hexpand(messages_g[i]->message_time, false);
    //         gtk_widget_set_vexpand(messages_g[i]->message_time, true);
    //         gtk_widget_set_halign(messages_g[i]->message_time, GTK_ALIGN_END);
    //         gtk_widget_set_valign(messages_g[i]->message_time, GTK_ALIGN_END);
    //         set_style_context(messages_g[i]->message_time, "message-time");

    //         messages_g[i]->message_text = gtk_label_new(message[i]->ms_text);
    //         gtk_widget_set_hexpand(messages_g[i]->message_text, false);
    //         gtk_widget_set_vexpand(messages_g[i]->message_text, true);
    //         gtk_widget_set_halign(messages_g[i]->message_text, GTK_ALIGN_START);
    //         gtk_label_set_line_wrap(GTK_LABEL(messages_g[i]->message_text), true);
    //         gtk_widget_set_size_request(messages_g[i]->message_text, 500, -1);
    //         set_style_context(messages_g[i]->message_text, "message-text");

    //         messages_g[i]->message_login = gtk_label_new(message[i]->ms_text);
    //         gtk_widget_set_hexpand(messages_g[i]->message_login, true);
    //         gtk_widget_set_halign(messages_g[i]->message_login, GTK_ALIGN_START);
    //         set_style_context(messages_g[i]->message_login, "contact-login");
    //         set_style_context(messages_g[i]->message_login, "message-from");

    //         css_set_for_one(messages_g[i]->event_box_message, "share/resources/css/main.css");
    //         css_set_for_one(messages_g[i]->message, "share/resources/css/main.css");
    //         css_set_for_one(messages_g[i]->message_info, "share/resources/css/main.css");
    //         css_set_for_one(messages_g[i]->message_time, "share/resources/css/main.css");
    //         css_set_for_one(messages_g[i]->message_text, "share/resources/css/main.css");
    //         css_set_for_one(messages_g[i]->message_login, "share/resources/css/main.css");

    //         gtk_grid_attach(GTK_GRID( messages_g[i]->message_info),  messages_g[i]->message_text, 0, 0, 1, 1);
    //         gtk_grid_attach(GTK_GRID( messages_g[i]->message_info),  messages_g[i]->message_time, 1, 0, 1, 1);

    //         gtk_grid_attach(GTK_GRID( messages_g[i]->message),  messages_g[i]->message_info, 0, 1, 1, 1);
    //         gtk_grid_attach(GTK_GRID( messages_g[i]->message),  messages_g[i]->message_login, 0, 0, 1, 1);


    //         gtk_container_add(GTK_CONTAINER(messages_g[i]->event_box_message),messages_g[i]->message);

    //         gtk_grid_attach(GTK_GRID(container_msg), messages_g[i]->event_box_message, 0, i, 1, 1);
    //     }
    //     gtk_widget_show_all(container_msg);
    //     //free_messages(message);
    // }
}
