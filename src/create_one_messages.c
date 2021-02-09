#include "chat.h"

void create_one_messages(int index, message_t *message)
{
    g_print("%d -- index\n",index);
    curr_chat.messages_g = (messages_t **)realloc(curr_chat.messages_g, sizeof(messages_t *) * (index + 2));
    if(curr_chat.messages_g == NULL){
        puts("Pizda");
    }
    curr_chat.messages_g[index] = (messages_t *)malloc(sizeof(messages_t));
    if(curr_chat.messages_g[index] == NULL){
        puts("Pizda index");
    }
    curr_chat.messages_g[index]->event_box_message = gtk_event_box_new();

    // g_signal_connect(G_OBJECT(chats_f.chat_items[i]->event_box_contact), "button-press-event", G_CALLBACK(open_click_chat), NULL);
    gtk_widget_set_hexpand(curr_chat.messages_g[index]->event_box_message, true);
    
    if (strcmp(message->u_id, data.user_id) == 0)
    {
        gtk_widget_set_halign(curr_chat.messages_g[index]->event_box_message, GTK_ALIGN_END);
    } else {
        gtk_widget_set_halign(curr_chat.messages_g[index]->event_box_message, GTK_ALIGN_START);
    }

    gtk_widget_set_vexpand(curr_chat.messages_g[index]->event_box_message, true);
    gtk_widget_set_name(curr_chat.messages_g[index]->event_box_message, message->ms_id);
    gtk_widget_set_size_request(curr_chat.messages_g[index]->event_box_message, 500, -1);

    curr_chat.messages_g[index]->message = gtk_grid_new();
    gtk_widget_set_name(curr_chat.messages_g[index]->message, message->ch_id);
    gtk_widget_set_hexpand(curr_chat.messages_g[index]->message, true);
    gtk_widget_set_vexpand(curr_chat.messages_g[index]->message, true);
    set_style_context(curr_chat.messages_g[index]->message, "message-body");

    curr_chat.messages_g[index]->message_info = gtk_grid_new();
    gtk_widget_set_hexpand(curr_chat.messages_g[index]->message_info, true);
    gtk_widget_set_vexpand(curr_chat.messages_g[index]->message_info, true);

    curr_chat.messages_g[index]->message_time = gtk_label_new(message->ms_datetime);
    gtk_widget_set_halign(curr_chat.messages_g[index]->message_time, GTK_ALIGN_END);
    set_style_context(curr_chat.messages_g[index]->message_time, "message-time");

    curr_chat.messages_g[index]->message_login = gtk_label_new(message->u_name);
    gtk_widget_set_hexpand(curr_chat.messages_g[index]->message_login, true);
    gtk_widget_set_halign(curr_chat.messages_g[index]->message_login, GTK_ALIGN_START);
    set_style_context(curr_chat.messages_g[index]->message_login, "contact-login");
    set_style_context(curr_chat.messages_g[index]->message_login, "message-from");
    
    curr_chat.messages_g[index]->message_text = gtk_label_new(message->ms_text);
    gtk_widget_set_hexpand(curr_chat.messages_g[index]->message_text, true);
    gtk_widget_set_vexpand(curr_chat.messages_g[index]->message_text, true);
    gtk_widget_set_halign(curr_chat.messages_g[index]->message_text, GTK_ALIGN_START);
    gtk_label_set_line_wrap(GTK_LABEL(curr_chat.messages_g[index]->message_text), true);
    gtk_widget_set_size_request(curr_chat.messages_g[index]->message_text, 500, -1);
    gtk_label_set_xalign(GTK_LABEL(curr_chat.messages_g[index]->message_text), 0);
    gtk_label_set_line_wrap_mode(GTK_LABEL(curr_chat.messages_g[index]->message_text), PANGO_WRAP_WORD_CHAR);
    gtk_label_set_max_width_chars(GTK_LABEL(curr_chat.messages_g[index]->message_text), 30);
    gtk_label_set_selectable(GTK_LABEL(curr_chat.messages_g[index]->message_text), true);
    set_style_context(curr_chat.messages_g[index]->message_text, "message-text");

    css_set_for_one(curr_chat.messages_g[index]->event_box_message,  data.main_theme_path);
    css_set_for_one(curr_chat.messages_g[index]->message,  data.main_theme_path);
    css_set_for_one(curr_chat.messages_g[index]->message_info,  data.main_theme_path);
    css_set_for_one(curr_chat.messages_g[index]->message_time,  data.main_theme_path);
    css_set_for_one(curr_chat.messages_g[index]->message_text,  data.main_theme_path);
    css_set_for_one(curr_chat.messages_g[index]->message_login,  data.main_theme_path);

    gtk_grid_attach(GTK_GRID(curr_chat.messages_g[index]->message_info), curr_chat.messages_g[index]->message_login, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(curr_chat.messages_g[index]->message_info), curr_chat.messages_g[index]->message_time, 1, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(curr_chat.messages_g[index]->message), curr_chat.messages_g[index]->message_text, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(curr_chat.messages_g[index]->message), curr_chat.messages_g[index]->message_info, 0, 0, 1, 1);

    gtk_container_add(GTK_CONTAINER(curr_chat.messages_g[index]->event_box_message), curr_chat.messages_g[index]->message);
    
    curr_chat.messages_g[index + 1] = NULL;
    *(curr_chat.length) = index + 1;
}
