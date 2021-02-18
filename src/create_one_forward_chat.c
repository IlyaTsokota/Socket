#include "chat.h"

void create_one_forward_chat(int index, chat_t *chat)
{
    chats_form_sec.chat_items = (chat_item_t **)realloc(chats_form_sec.chat_items, sizeof(chat_item_t *) * (index + 2));
    chats_form_sec.chat_items[index] = (chat_item_t *)malloc(sizeof(chat_item_t));

    chats_form_sec.chat_items[index]->event_box_contact = gtk_event_box_new();

    gtk_widget_set_hexpand(chats_form_sec.chat_items[index]->event_box_contact, true);
    gtk_widget_set_vexpand(chats_form_sec.chat_items[index]->event_box_contact, false);
    gtk_widget_set_name(chats_form_sec.chat_items[index]->event_box_contact, chat->ch_id);
    g_signal_connect(G_OBJECT(chats_form_sec.chat_items[index]->event_box_contact), "button-press-event", G_CALLBACK(open_click_chat), NULL);

    gtk_widget_set_valign(chats_form_sec.chat_items[index]->event_box_contact, GTK_ALIGN_START);

    chats_form_sec.chat_items[index]->contact_container = gtk_grid_new();
    gtk_widget_set_hexpand(chats_form_sec.chat_items[index]->contact_container, false);
    gtk_widget_set_vexpand(chats_form_sec.chat_items[index]->contact_container, true);
    gtk_widget_set_size_request(chats_form_sec.chat_items[index]->contact_container, -1, 84);
    set_style_context(chats_form_sec.chat_items[index]->contact_container, "contact-container");

    chats_form_sec.chat_items[index]->time_last_message = gtk_label_new("");

    chats_form_sec.chat_items[index]->contact_info = gtk_grid_new();
    gtk_widget_set_hexpand(chats_form_sec.chat_items[index]->contact_info, true);
    gtk_widget_set_vexpand(chats_form_sec.chat_items[index]->contact_info, true);
    set_style_context(chats_form_sec.chat_items[index]->contact_info, "contact-body");

    chats_form_sec.chat_items[index]->contact_last_msg = gtk_grid_new();
    gtk_widget_set_valign(chats_form_sec.chat_items[index]->contact_last_msg, GTK_ALIGN_END);
    gtk_widget_set_hexpand(chats_form_sec.chat_items[index]->contact_last_msg, true);
    gtk_widget_set_vexpand(chats_form_sec.chat_items[index]->contact_last_msg, true);

    chats_form_sec.chat_items[index]->text_last_message = gtk_label_new("");

    chats_form_sec.chat_items[index]->login_last_message = gtk_label_new("");
   
    chats_form_sec.chat_items[index]->contact_name_container = gtk_grid_new();

    chats_form_sec.chat_items[index]->contact_name_lable = strcmp(chat->u_login, "0") == 0 ? gtk_label_new(chat->ch_name) : gtk_label_new(chat->u_login);

    gtk_widget_set_margin_top(chats_form_sec.chat_items[index]->contact_name_lable, 10);
    gtk_widget_set_halign(chats_form_sec.chat_items[index]->contact_name_lable, GTK_ALIGN_START);
    set_style_context(chats_form_sec.chat_items[index]->contact_name_lable, "contact-login");

    chats_form_sec.chat_items[index]->user_is_online = gtk_grid_new();
    gtk_widget_set_size_request(chats_form_sec.chat_items[index]->user_is_online, 10, 10);
    gtk_widget_set_halign(chats_form_sec.chat_items[index]->user_is_online, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(chats_form_sec.chat_items[index]->user_is_online, GTK_ALIGN_START);
    gtk_widget_set_hexpand(chats_form_sec.chat_items[index]->user_is_online, false);
    gtk_widget_set_vexpand(chats_form_sec.chat_items[index]->user_is_online, true);
    set_style_context(chats_form_sec.chat_items[index]->user_is_online, "is-online");

    chats_form_sec.chat_items[index]->user_is_online_round = gtk_level_bar_new();

    //}

    chats_form_sec.chat_items[index]->contact_img_container = gtk_grid_new();
    gtk_widget_set_size_request(chats_form_sec.chat_items[index]->contact_img_container, 57, 57);
    gtk_widget_set_halign(chats_form_sec.chat_items[index]->contact_img_container, GTK_ALIGN_START);
    gtk_widget_set_valign(chats_form_sec.chat_items[index]->contact_img_container, GTK_ALIGN_CENTER);
    gtk_widget_set_hexpand(chats_form_sec.chat_items[index]->contact_img_container, false);
    gtk_widget_set_vexpand(chats_form_sec.chat_items[index]->contact_img_container, false);
    set_style_context(chats_form_sec.chat_items[index]->contact_img_container, "contact-img");

    char *filename;
    chats_form_sec.chat_items[index]->img_contact = gtk_image_new();

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
    gtk_image_set_from_pixbuf(GTK_IMAGE(chats_form_sec.chat_items[index]->img_contact), pixbuf);
    free(filename);

    gtk_widget_set_hexpand(chats_form_sec.chat_items[index]->img_contact, true);
    gtk_widget_set_vexpand(chats_form_sec.chat_items[index]->img_contact, true);
    set_style_context(chats_form_sec.chat_items[index]->img_contact, "contact-icon");

    css_set_for_one(chats_form_sec.chat_items[index]->contact_container, data.main_theme_path);
    css_set_for_one(chats_form_sec.chat_items[index]->time_last_message, data.main_theme_path);
    css_set_for_one(chats_form_sec.chat_items[index]->contact_info, data.main_theme_path);
    css_set_for_one(chats_form_sec.chat_items[index]->text_last_message, data.main_theme_path);
    css_set_for_one(chats_form_sec.chat_items[index]->login_last_message, data.main_theme_path);

    css_set_for_one(chats_form_sec.chat_items[index]->contact_img_container, data.main_theme_path);
    css_set_for_one(chats_form_sec.chat_items[index]->img_contact, data.main_theme_path);
    css_set_for_one(chats_form_sec.chat_items[index]->contact_name_lable, data.main_theme_path);

    gtk_grid_attach(GTK_GRID(chats_form_sec.chat_items[index]->contact_container), chats_form_sec.chat_items[index]->contact_img_container, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(chats_form_sec.chat_items[index]->contact_img_container), chats_form_sec.chat_items[index]->img_contact, 0, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(chats_form_sec.chat_items[index]->contact_container), chats_form_sec.chat_items[index]->contact_info, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(chats_form_sec.chat_items[index]->contact_info), chats_form_sec.chat_items[index]->contact_last_msg, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(chats_form_sec.chat_items[index]->contact_last_msg), chats_form_sec.chat_items[index]->login_last_message, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(chats_form_sec.chat_items[index]->contact_last_msg), chats_form_sec.chat_items[index]->text_last_message, 1, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(chats_form_sec.chat_items[index]->contact_info), chats_form_sec.chat_items[index]->contact_name_container, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(chats_form_sec.chat_items[index]->contact_name_container), chats_form_sec.chat_items[index]->contact_name_lable, 0, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(chats_form_sec.chat_items[index]->user_is_online), chats_form_sec.chat_items[index]->user_is_online_round, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(chats_form_sec.chat_items[index]->contact_name_container), chats_form_sec.chat_items[index]->user_is_online, 1, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(chats_form_sec.chat_items[index]->contact_container), chats_form_sec.chat_items[index]->time_last_message, 2, 0, 1, 1);

    gtk_container_add(GTK_CONTAINER(chats_form_sec.chat_items[index]->event_box_contact), chats_form_sec.chat_items[index]->contact_container);
    chats_form_sec.chat_items[index + 1] = NULL;
    chats_form_sec.size = index + 1;
    if (chats_form_sec.curr_chat == NULL)
    {
        chats_form_sec.curr_chat = strdup(chat->ch_id);
    }
}

