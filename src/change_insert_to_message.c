#include "chat.h"

gboolean change_insert_to_message(gpointer widget)
{

    GtkAdjustment *adjustment = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW((GtkWidget *)widget));
    gtk_adjustment_set_value(adjustment, gtk_adjustment_get_upper(adjustment) + 100);

    return false;
}

gboolean refresh_chat(gpointer d)
{
    g_mutex_lock(&main_form.mutex_update);
    struct sockaddr_in client_addr;
    update_t *update = malloc(sizeof(update_t));
    update->socket = socket(AF_INET, SOCK_STREAM, 0);
    int port = data.port;
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = INADDR_ANY;
    client_addr.sin_port = htons(port);

    if (connect(update->socket, (struct sockaddr *)&client_addr, sizeof(client_addr)) == 0)
    {
        // char *hmsg = strdup("1");
        // write(update->socket, hmsg, 1);
        // free(hmsg);
        message_arr *messages = take_messages(update->socket, data.user_id, main_form.last_ms_id);
        if (messages != NULL)
        {

            int messages_length = *(messages->length);
            int length = *(curr_chat.length);
            int j = length;

            for (int i = 0; i < messages_length; i++)
            {
                create_one_messages(j++, messages->messages[i]);
            }
            // update_chat(update);
            char *time = NULL;
            char *last_msg = NULL;
            char *last_login = NULL;
            char *time_temp;
            char *last_msg_temp;
            char *last_login_temp;
            for (int i = 0; i < chats_f.size; i++)
            {
                for (int j = *(curr_chat.length) - 1; j > 0; j--)
                {
                    if (chats_f.chat_items[i] != NULL && strcmp((char *)gtk_widget_get_name(curr_chat.messages_g[j]->message), (char *)gtk_widget_get_name(chats_f.chat_items[i]->event_box_contact)) == 0)
                    {
                        time_temp = (char *)gtk_label_get_text(GTK_LABEL(curr_chat.messages_g[j]->message_time));
                        time = strdup(&time_temp[11]);
                        gtk_label_set_text(GTK_LABEL(chats_f.chat_items[i]->time_last_message), time);
                        if (GTK_IS_LABEL(curr_chat.messages_g[j]->message_text))
                        {
                            last_msg_temp = (char *)gtk_label_get_text(GTK_LABEL(curr_chat.messages_g[j]->message_text));
                        }
                        else
                        {
                            last_msg_temp = "Image";
                        }
                        last_msg = cut_str(last_msg_temp, 10);
                        gtk_label_set_text(GTK_LABEL(chats_f.chat_items[i]->text_last_message), last_msg);
                        last_login_temp = (char *)gtk_label_get_text(GTK_LABEL(curr_chat.messages_g[j]->message_login));
                        last_login = strjoin(2, last_login_temp, ":");
                        gtk_label_set_text(GTK_LABEL(chats_f.chat_items[i]->login_last_message), last_login);
                        free(time);
                        free(last_msg);
                        free(last_login);
                        break;
                    }
                }
            }
            free(main_form.last_ms_id);

            main_form.last_ms_id = strdup(messages->messages[messages_length - 1]->ms_id);
            j = length;
            for (int i = j; i < length + messages_length; i++)
            {

                if (strcmp(chats_f.curr_chat, (char *)gtk_widget_get_name(curr_chat.messages_g[i]->message)) == 0)
                {
                    gtk_grid_attach(GTK_GRID(main_form.message_line), curr_chat.messages_g[i]->event_box_message, 0, i, 1, 1);
                    g_timeout_add(100, change_insert_to_message, main_form.message_scroll);
                }
            }
            gtk_widget_show_all(main_form.message_line);

            free_messages(messages);
        }
        g_mutex_unlock(&main_form.mutex_update);
        close(update->socket);
        free(update);
        update = NULL;
    }
    return true;
}

gboolean update_chat(gpointer d)
{
    struct sockaddr_in client_addr;
    update_t *update = malloc(sizeof(update_t));
    update->socket = socket(AF_INET, SOCK_STREAM, 0);
    int port = data.port;
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = INADDR_ANY;
    client_addr.sin_port = htons(port);

    if (connect(update->socket, (struct sockaddr *)&client_addr, sizeof(client_addr)) == 0)
    {
        g_mutex_lock(&main_form.mutex_file_transfer);
        chat_t **chats = take_chats(data.user_id, update->socket);
        if (chats != NULL)
        {
            chats_f.was_free = false;
            int size = 0;
            for (size_t i = 0; chats[i]; i++)
            {
                size++;
            }
            sort_chats(chats, size);
            //puts("In");
            for (int i = 0; i < size; i++)
            {
                //puts("In3");

                if (chats_f.chat_items[i] != NULL && chats[i] == NULL)
                {
                    //puts("In4");

                    free_one_chat_widgets(chats_f.chat_items[i]);
                }
                else if (chats_f.chat_items[i] != NULL && chats[i] != NULL)
                {

                    if (strcmp(chats[i]->u_login, "0") == 0)
                    {
                        gtk_label_set_text(GTK_LABEL(chats_f.chat_items[i]->contact_name_lable), chats[i]->ch_name);
                    }
                    else
                    {
                        gtk_label_set_text(GTK_LABEL(chats_f.chat_items[i]->contact_name_lable), chats[i]->u_login);
                    }

                    gtk_widget_set_name(chats_f.chat_items[i]->event_box_contact, chats[i]->ch_id);
                    g_signal_handlers_disconnect_by_func(chats_f.chat_items[i]->event_box_contact, open_click_chat, NULL);
                    g_signal_connect(G_OBJECT(chats_f.chat_items[i]->event_box_contact), "button-press-event", G_CALLBACK(open_click_chat), NULL);

                    char *filename;
                    if (strcmp(chats[i]->ch_avatar, "no_avatar") == 0 || strcmp(chats[i]->ch_avatar, "1234") == 0)
                    {
                        if (strcmp(chats[i]->u_avatar, "0") == 0 || strcmp(chats[i]->u_avatar, "1234") == 0)
                        {
                            if (strcmp(chats[i]->u_login, "Saved Messages") == 0)
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
                            filename = get_profile_img(data.socket_desc, chats[i]->u_avatar, chats[i]->ch_id, true);
                        }
                    }
                    else
                    {
                        filename = get_chat_img(data.socket_desc, chats[i]->ch_id, chats[i]->ch_avatar);
                    }

                    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(filename, 55, 55, TRUE, NULL);
                    gtk_image_set_from_pixbuf(GTK_IMAGE(chats_f.chat_items[i]->img_contact), pixbuf);
                    free(filename);
                }
                else
                {
                    create_one_chat(i, chats[i]);
                    gtk_grid_attach(GTK_GRID(main_form.chats_grid), chats_f.chat_items[i]->event_box_contact, 0, i, 1, 1);
                    gtk_widget_show_all(main_form.left_content[0]);
                }
            }

            int curr_index = 0;
            for (int i = 0; i < size; i++)
            {
                if (strcmp(chats_f.curr_chat, (char *)gtk_widget_get_name(chats_f.chat_items[i]->event_box_contact)))
                {
                    curr_index = i;
                }
            }
            clear_style_all_chat_widgets();
            char *color = strcmp(data.theme, "Dark") == 0 ? strdup("* { background-color: #3c3c3c;}")
                                                          : strdup("* { background-color: #ebf3f7;}");
            edit_styles_for_widget(chats_f.chat_items[curr_index]->event_box_contact, color);
            free(color);
            free_chats(chats);
        }
        g_mutex_unlock(&main_form.mutex_file_transfer);
    }
    close(update->socket);
    free(update);

    return true;
}

gboolean update_edit_msgs(gpointer d)
{

    g_mutex_lock(&main_form.mutex_update);
    struct sockaddr_in client_addr;
    update_t *update = malloc(sizeof(update_t));
    update->socket = socket(AF_INET, SOCK_STREAM, 0);
    int port = data.port;
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = INADDR_ANY;
    client_addr.sin_port = htons(port);

    if (connect(update->socket, (struct sockaddr *)&client_addr, sizeof(client_addr)) == 0)
    {
        message_back_info_t **messages = take_edit_messages(update->socket);
        if (messages != NULL)
        {
            if (curr_chat.messages_g != NULL)
            {
                int j = 0;
                for (int i = 0; curr_chat.messages_g[i]; i++)
                {
                    if ((strcmp(messages[j]->ms_id, (char *)gtk_widget_get_name(curr_chat.messages_g[i]->event_box_message)) == 0) && GTK_IS_LABEL(curr_chat.messages_g[i]->message_text) && !(strcmp(gtk_label_get_text(GTK_LABEL(curr_chat.messages_g[i]->edited)), "") != 0))
                    {
                        gtk_label_set_text(GTK_LABEL(curr_chat.messages_g[i]->edited), "[Edited]");
                        gtk_label_set_text(GTK_LABEL(curr_chat.messages_g[i]->message_text), messages[j]->ms_text);
                        j++;
                    }
                }
                free_message_back_info_s(messages);
            }
        }
    }
    g_mutex_unlock(&main_form.mutex_update);
    close(update->socket);
    free(update);
    return true;
}
