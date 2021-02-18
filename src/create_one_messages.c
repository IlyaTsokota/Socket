#include "chat.h"

void create_one_messages(int index, message_t *message)
{
    curr_chat.messages_g = (messages_t **)realloc(curr_chat.messages_g, sizeof(user_by_chat_t *) * (index + 2));
    curr_chat.messages_g[index] = (messages_t *)malloc(sizeof(messages_t));
    curr_chat.messages_g[index]->event_box_message = gtk_event_box_new();

    // g_signal_connect(G_OBJECT(chats_f.chat_items[i]->event_box_contact), "button-press-event", G_CALLBACK(open_click_chat), NULL);
    gtk_widget_set_hexpand(curr_chat.messages_g[index]->event_box_message, true);

    if (strcmp(message->u_id, data.user_id) == 0)
    {
        gtk_widget_set_halign(curr_chat.messages_g[index]->event_box_message, GTK_ALIGN_END);
    }
    else
    {
        gtk_widget_set_halign(curr_chat.messages_g[index]->event_box_message, GTK_ALIGN_START);
    }

    gtk_widget_set_vexpand(curr_chat.messages_g[index]->event_box_message, true);
    gtk_widget_set_name(curr_chat.messages_g[index]->event_box_message, message->ms_id);
    // gtk_widget_set_size_request(curr_chat.messages_g[index]->event_box_message, 300, -1);

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

    if (strcmp(message->ms_ismedia, "0") == 0)
    {
        curr_chat.messages_g[index]->message_text = gtk_label_new(message->ms_text);
        gtk_widget_set_hexpand(curr_chat.messages_g[index]->message_text, true);
        gtk_widget_set_vexpand(curr_chat.messages_g[index]->message_text, true);
        gtk_widget_set_halign(curr_chat.messages_g[index]->message_text, GTK_ALIGN_START);
        gtk_label_set_line_wrap(GTK_LABEL(curr_chat.messages_g[index]->message_text), true);
        // gtk_widget_set_size_request(curr_chat.messages_g[index]->message_text, 500, -1);
        gtk_label_set_xalign(GTK_LABEL(curr_chat.messages_g[index]->message_text), 0);
        gtk_label_set_line_wrap_mode(GTK_LABEL(curr_chat.messages_g[index]->message_text), PANGO_WRAP_WORD_CHAR);
        gtk_label_set_max_width_chars(GTK_LABEL(curr_chat.messages_g[index]->message_text), 50);
        gtk_label_set_selectable(GTK_LABEL(curr_chat.messages_g[index]->message_text), true);
    }
    else
    {

        curr_chat.messages_g[index]->message_text = gtk_image_new();

        char *filename = get_msg_img(data.socket_desc, message->ch_id, message->ms_id, message->ms_text);
        gint width, height;
        cairo_surface_t *image = cairo_image_surface_create_from_png(filename);
        width = cairo_image_surface_get_width(image);
        if (width > 500)
            width = 500;

        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(filename, width, -1, TRUE, NULL);
        gtk_image_set_from_pixbuf(GTK_IMAGE(curr_chat.messages_g[index]->message_text), pixbuf);
        cairo_surface_destroy(image);
    }
    g_signal_connect(G_OBJECT(curr_chat.messages_g[index]->event_box_message), "button-press-event", G_CALLBACK(click_on_msg), curr_chat.messages_g[index]->message_text);

    char *edited_text = strcmp(message->ms_isedited, "1") == 0 ? strdup("[Edited]") : strdup("");
    curr_chat.messages_g[index]->edited = gtk_label_new(edited_text);
    gtk_widget_set_hexpand(curr_chat.messages_g[index]->edited, true);
    gtk_widget_set_halign(curr_chat.messages_g[index]->edited, GTK_ALIGN_END);
    gtk_widget_set_valign(curr_chat.messages_g[index]->edited, GTK_ALIGN_END);
    if(strcmp(message->ms_isedited, "1") == 0){
    gtk_widget_set_margin_bottom(curr_chat.messages_g[index]->edited, 10);
    gtk_widget_set_margin_end(curr_chat.messages_g[index]->edited, 10);
    }
    free(edited_text);

    set_style_context(curr_chat.messages_g[index]->message_time, "message-time");
    set_style_context(curr_chat.messages_g[index]->message_text, "message-text");

    css_set_for_one(curr_chat.messages_g[index]->event_box_message, data.main_theme_path);
    css_set_for_one(curr_chat.messages_g[index]->edited, data.main_theme_path);
    css_set_for_one(curr_chat.messages_g[index]->message, data.main_theme_path);
    css_set_for_one(curr_chat.messages_g[index]->message_info, data.main_theme_path);
    css_set_for_one(curr_chat.messages_g[index]->message_time, data.main_theme_path);
    css_set_for_one(curr_chat.messages_g[index]->message_text, data.main_theme_path);
    css_set_for_one(curr_chat.messages_g[index]->message_login, data.main_theme_path);

    gtk_grid_attach(GTK_GRID(curr_chat.messages_g[index]->message_info), curr_chat.messages_g[index]->message_login, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(curr_chat.messages_g[index]->message_info), curr_chat.messages_g[index]->message_time, 1, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(curr_chat.messages_g[index]->message), curr_chat.messages_g[index]->message_text, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(curr_chat.messages_g[index]->message), curr_chat.messages_g[index]->edited, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(curr_chat.messages_g[index]->message), curr_chat.messages_g[index]->message_info, 0, 0, 1, 1);

    gtk_container_add(GTK_CONTAINER(curr_chat.messages_g[index]->event_box_message), curr_chat.messages_g[index]->message);

    curr_chat.messages_g[index + 1] = NULL;
    *(curr_chat.length) = index + 1;
}

int get_curr_msg_index(char *id)
{
    int index = 0;
    if (curr_chat.messages_g != NULL)
    {
        for (ssize_t j = *(curr_chat.length) - 1; j >= 0; j--)
        {
            char *ms_id = (char *)gtk_widget_get_name(curr_chat.messages_g[j]->event_box_message);
            if (strcmp(ms_id, id) == 0)
            {
                index = j;
                break;
            }
        }
    }
    return index;
}