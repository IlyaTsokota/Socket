#include "chat.h"

gboolean change_insert_to_message(gpointer widget)
{
    GtkAdjustment *adjustment = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW((GtkWidget *)widget));
    gtk_adjustment_set_value(adjustment, gtk_adjustment_get_upper(adjustment));
    return false;
}

gboolean refresh_chat()
{

    message_arr *messages = take_messages(data.user_id, main_form.last_ms_id);
    if ( messages != NULL)
    {
        int j = *(curr_chat.length);
        for (int i = 0; i < *messages->length; i++)
        {
            create_one_messages(j++, messages->messages[i]);
        }
        free(main_form.last_ms_id);
        main_form.last_ms_id = strdup(int_to_str(j));
        if (main_form.current_panel_id == 2)
        {
            j = *(curr_chat.length);
            for (int i = j; i < j + *(messages->length); i++)
            {
                if (strcmp(chats_f.curr_chat, (char *)gtk_widget_get_name(curr_chat.messages_g[i]->message)) == 0)
                {
                    gtk_grid_attach(GTK_GRID(main_form.message_line), curr_chat.messages_g[i]->event_box_message, 0, j++, 1, 1);
                }
            }
            gtk_widget_show_all(main_form.message_line);
        }
        free_messages(messages);
    }
    // if (main_form.current_panel_id == 2)
    // {
    //     char *last_ms_id = get_last_mesage_id("messages.json");
    //     get_all_messages(data.user_id, last_ms_id);
    //     free(last_ms_id);
    //     //g_timeout_add(50, change_insert_to_message, main_form.message_scroll);
    //     gtk_widget_destroy(main_form.left_content);
    //     show_chats(main_form.main_grid);
    //     message_arr *message_last = get_messages_from_file("messages.json", chats_f.curr_chat);
    //     g_print("%s\n", mx_file_to_str("messages.json"));
    //     if (curr_chat.length > 1)
    //     {
    //         puts("Vse idet po plany");
    //         char *last_id = (char *)gtk_widget_get_name(curr_chat.messages_g[*message_last->length - 1]->event_box_message);
    //         puts(last_id);
    //         puts( message_last->messages[*message_last->length - 1]->ms_id);
    //         puts("----------------");
    //         if (strcmp(last_id, message_last->messages[*message_last->length - 1]->ms_id) == 0)
    //         {
    //             free_messages(message_last);
    //             return true;
    //         }
    //     }
    //     for (int i = curr_chat.length -1; i < *message_last->length; i++)
    //     {
    //         create_one_messages(*message_last->length, message_last->messages[i], main_form.message_line);
    //     }
    //     gtk_widget_show_all(main_form.message_line);
    //     free_messages(message_last);
    // }
    return true;
}
