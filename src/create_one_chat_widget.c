#include "chat.h"

void create_one_chat(int index, chat_t *chat)
{
    chats_f.chat_items = (chat_item_t **)realloc(chats_f.chat_items, sizeof(chat_item_t *) * (index + 2));
    chats_f.chat_items[index] = (chat_item_t *)malloc(sizeof(chat_item_t));

    chats_f.chat_items[index]->event_box_contact = gtk_event_box_new();

    gtk_widget_set_hexpand(chats_f.chat_items[index]->event_box_contact, true);
    gtk_widget_set_vexpand(chats_f.chat_items[index]->event_box_contact, false);
    gtk_widget_set_name(chats_f.chat_items[index]->event_box_contact, chat->ch_id);
    g_signal_connect(G_OBJECT(chats_f.chat_items[index]->event_box_contact), "button-press-event", G_CALLBACK(open_click_chat), NULL);

    gtk_widget_set_valign(chats_f.chat_items[index]->event_box_contact, GTK_ALIGN_START);

    int last_msg_index = -1;
    if (curr_chat.messages_g != NULL)
    {
        for (ssize_t j = *(curr_chat.length) - 1; j >= 0; j--)
        {
            char *ms_id = (char *)gtk_widget_get_name(curr_chat.messages_g[j]->message);
            if (strcmp(ms_id, chat->ch_id) == 0)
            {
                last_msg_index = j;
                break;
            }
        }
    }

    chats_f.chat_items[index]->contact_container = gtk_grid_new();
    gtk_widget_set_hexpand(chats_f.chat_items[index]->contact_container, false);
    gtk_widget_set_vexpand(chats_f.chat_items[index]->contact_container, true);
    gtk_widget_set_size_request(chats_f.chat_items[index]->contact_container, -1, 84);
    set_style_context(chats_f.chat_items[index]->contact_container, "contact-container");

    char *time;
    if (last_msg_index != -1)
    {
        time = strdup(&gtk_label_get_text(GTK_LABEL(curr_chat.messages_g[last_msg_index]->message_time))[11]);
    }
    else
    {
        time = strdup("");
    }

    chats_f.chat_items[index]->time_last_message = gtk_label_new(time);
    gtk_widget_set_valign(chats_f.chat_items[index]->time_last_message, GTK_ALIGN_START);
    gtk_widget_set_hexpand(chats_f.chat_items[index]->time_last_message, false);
    gtk_widget_set_vexpand(chats_f.chat_items[index]->time_last_message, true);
    gtk_widget_set_margin_top(chats_f.chat_items[index]->time_last_message, 10);
    free(time);
    set_style_context(chats_f.chat_items[index]->time_last_message, "contact-time");

    chats_f.chat_items[index]->contact_info = gtk_grid_new();
    gtk_widget_set_hexpand(chats_f.chat_items[index]->contact_info, true);
    gtk_widget_set_vexpand(chats_f.chat_items[index]->contact_info, true);
    set_style_context(chats_f.chat_items[index]->contact_info, "contact-body");

    chats_f.chat_items[index]->contact_last_msg = gtk_grid_new();
    gtk_widget_set_valign(chats_f.chat_items[index]->contact_last_msg, GTK_ALIGN_END);
    gtk_widget_set_hexpand(chats_f.chat_items[index]->contact_last_msg, true);
    gtk_widget_set_vexpand(chats_f.chat_items[index]->contact_last_msg, true);

    char *last_msg;
    if (last_msg_index != -1)
    {
        if (GTK_IS_LABEL(curr_chat.messages_g[last_msg_index]->message_text))
        {
            last_msg = cut_str((char *)gtk_label_get_text(GTK_LABEL(curr_chat.messages_g[last_msg_index]->message_text)), 10);
        }
        else
        {
            last_msg = strdup("Image");
        }
    }
    else
    {
        last_msg = strdup("");
    }

    chats_f.chat_items[index]->text_last_message = gtk_label_new(last_msg);
    gtk_widget_set_hexpand(chats_f.chat_items[index]->text_last_message, false);
    set_style_context(chats_f.chat_items[index]->text_last_message, "contact-lastmsg");
    set_style_context(chats_f.chat_items[index]->text_last_message, "contact-lastmessage");
    free(last_msg);

    char *last_login;
    if (last_msg_index != -1)
    {
        last_login = strjoin(2, (char *)gtk_label_get_text(GTK_LABEL(curr_chat.messages_g[last_msg_index]->message_login)), ":");
    }
    else
    {
        last_login = strdup(" ");
    }

    chats_f.chat_items[index]->login_last_message = gtk_label_new(last_login);
    gtk_widget_set_valign(chats_f.chat_items[index]->login_last_message, GTK_ALIGN_START);
    gtk_widget_set_hexpand(chats_f.chat_items[index]->login_last_message, false);
    set_style_context(chats_f.chat_items[index]->login_last_message, "contact-lastmessage");
    free(last_login);

    chats_f.chat_items[index]->contact_name_container = gtk_grid_new();

    chats_f.chat_items[index]->contact_name_lable = strcmp(chat->u_login, "0") == 0 ? gtk_label_new(chat->ch_name) : gtk_label_new(chat->u_login);

    gtk_widget_set_margin_top(chats_f.chat_items[index]->contact_name_lable, 10);
    gtk_widget_set_halign(chats_f.chat_items[index]->contact_name_lable, GTK_ALIGN_START);
    set_style_context(chats_f.chat_items[index]->contact_name_lable, "contact-login");

    // if (is_online(chats[index]->u_lastSeen) && !(strcmp(chats[index]->u_login, "0") == 0))
    // {
    chats_f.chat_items[index]->user_is_online = gtk_grid_new();
    gtk_widget_set_size_request(chats_f.chat_items[index]->user_is_online, 10, 10);
    gtk_widget_set_halign(chats_f.chat_items[index]->user_is_online, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(chats_f.chat_items[index]->user_is_online, GTK_ALIGN_START);
    gtk_widget_set_hexpand(chats_f.chat_items[index]->user_is_online, false);
    gtk_widget_set_vexpand(chats_f.chat_items[index]->user_is_online, true);
    set_style_context(chats_f.chat_items[index]->user_is_online, "is-online");

    chats_f.chat_items[index]->user_is_online_round = gtk_level_bar_new();
    gtk_widget_set_opacity(chats_f.chat_items[index]->user_is_online_round, 0);
    if (strcmp(chat->ch_name, "personal_chat") != 0)
    {
        gtk_widget_set_opacity(chats_f.chat_items[index]->user_is_online, 0);
    }

    css_set_for_one(chats_f.chat_items[index]->user_is_online, data.main_theme_path);

    // }

    chats_f.chat_items[index]->contact_img_container = gtk_grid_new();
    gtk_widget_set_size_request(chats_f.chat_items[index]->contact_img_container, 57, 57);
    gtk_widget_set_halign(chats_f.chat_items[index]->contact_img_container, GTK_ALIGN_START);
    gtk_widget_set_valign(chats_f.chat_items[index]->contact_img_container, GTK_ALIGN_CENTER);
    gtk_widget_set_hexpand(chats_f.chat_items[index]->contact_img_container, false);
    gtk_widget_set_vexpand(chats_f.chat_items[index]->contact_img_container, false);
    set_style_context(chats_f.chat_items[index]->contact_img_container, "contact-img");

    char *filename;
    chats_f.chat_items[index]->img_contact = gtk_image_new();

    if (strcmp(chat->ch_avatar, "no_avatar") == 0 || strcmp(chat->ch_avatar, "1234") == 0)
    {
        if (strcmp(chat->u_avatar, "0") == 0 || strcmp(chat->u_avatar, "1234") == 0)
        {
            if (strcmp(chat->u_login, "Saved Messages") == 0)
            {
                filename = strdup("share/resources/img/ava2SavedMessages.png");
            }
            else
            {
                filename = strdup("share/resources/img/ava2.png");
            }
        }
        else
        {
            filename = get_profile_img(data.socket_desc, chat->u_avatar, chat->ch_id, true);
        }
    }
    else
    {
        filename = get_chat_img(data.socket_desc, chat->ch_id, chat->ch_avatar);
    }
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(filename, 55, 55, TRUE, NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE(chats_f.chat_items[index]->img_contact), pixbuf);
    free(filename);

    gtk_widget_set_hexpand(chats_f.chat_items[index]->img_contact, true);
    gtk_widget_set_vexpand(chats_f.chat_items[index]->img_contact, true);
    set_style_context(chats_f.chat_items[index]->img_contact, "contact-icon");

    css_set_for_one(chats_f.chat_items[index]->contact_container, data.main_theme_path);
    css_set_for_one(chats_f.chat_items[index]->time_last_message, data.main_theme_path);
    css_set_for_one(chats_f.chat_items[index]->contact_info, data.main_theme_path);
    css_set_for_one(chats_f.chat_items[index]->text_last_message, data.main_theme_path);
    css_set_for_one(chats_f.chat_items[index]->login_last_message, data.main_theme_path);

    css_set_for_one(chats_f.chat_items[index]->contact_img_container, data.main_theme_path);
    css_set_for_one(chats_f.chat_items[index]->img_contact, data.main_theme_path);
    css_set_for_one(chats_f.chat_items[index]->contact_name_lable, data.main_theme_path);

    gtk_grid_attach(GTK_GRID(chats_f.chat_items[index]->contact_container), chats_f.chat_items[index]->contact_img_container, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(chats_f.chat_items[index]->contact_img_container), chats_f.chat_items[index]->img_contact, 0, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(chats_f.chat_items[index]->contact_container), chats_f.chat_items[index]->contact_info, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(chats_f.chat_items[index]->contact_info), chats_f.chat_items[index]->contact_last_msg, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(chats_f.chat_items[index]->contact_last_msg), chats_f.chat_items[index]->login_last_message, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(chats_f.chat_items[index]->contact_last_msg), chats_f.chat_items[index]->text_last_message, 1, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(chats_f.chat_items[index]->contact_info), chats_f.chat_items[index]->contact_name_container, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(chats_f.chat_items[index]->contact_name_container), chats_f.chat_items[index]->contact_name_lable, 0, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(chats_f.chat_items[index]->user_is_online), chats_f.chat_items[index]->user_is_online_round, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(chats_f.chat_items[index]->contact_name_container), chats_f.chat_items[index]->user_is_online, 1, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(chats_f.chat_items[index]->contact_container), chats_f.chat_items[index]->time_last_message, 2, 0, 1, 1);

    gtk_container_add(GTK_CONTAINER(chats_f.chat_items[index]->event_box_contact), chats_f.chat_items[index]->contact_container);
    chats_f.chat_items[index + 1] = NULL;
    chats_f.size = index + 1;
    if (chats_f.curr_chat == NULL)
    {
        chats_f.curr_chat = strdup(chat->ch_id);
    }
}
