#include "chat.h"

gboolean change_insert_to_message(gpointer widget)
{
    GtkAdjustment *adjustment = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW((GtkWidget *)widget));
    gtk_adjustment_set_value(adjustment, gtk_adjustment_get_upper(adjustment));
    return false;
}

gboolean refresh_chat(update_t *update)
{
    puts("IN");
    message_arr *messages = take_messages(update->socket, data.user_id, main_form.last_ms_id);
    g_mutex_lock(&main_form.mutex);
    if (messages != NULL)
    {
        int messages_length = *(messages->length);
        int length = *(curr_chat.length);
        int j = length;

        for (int i = 0; i < messages_length; i++)
        {
            create_one_messages(j++, messages->messages[i]);
        }

        char *time = NULL;
        char *last_msg = NULL;
        char *last_login = NULL;
        char *time_temp;
        char *last_msg_temp;
        char *last_login_temp;

        for (int i = 0; chats_f.chat_items[i]; i++)
        {
            for (int j = *(curr_chat.length) - 1; j > 0; j--)
            {
                if (strcmp((char *)gtk_widget_get_name(curr_chat.messages_g[j]->message), (char *)gtk_widget_get_name(chats_f.chat_items[i]->event_box_contact)) == 0)
                {
                    time_temp = (char *)gtk_label_get_text(GTK_LABEL(curr_chat.messages_g[j]->message_time));
                    time = strdup(&time_temp[11]);
                    gtk_label_set_text(GTK_LABEL(chats_f.chat_items[i]->time_last_message), time);
                    last_msg_temp = (char *)gtk_label_get_text(GTK_LABEL(curr_chat.messages_g[j]->message_text));
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
            }
        }
        gtk_widget_show_all(main_form.message_line);

        free_messages(messages);
    }

    g_mutex_unlock(&main_form.mutex);
    puts("OUT");

    return true;
}

gboolean update_chat(update_t *update)
{
    // sort_by_chat_widget();
    // free_chat_widgets(chats_f.chat_items);
    // create_chat_widgets(data.user_id, update->socket);
    // show_chats_widgets();
    return true;
}
