#include "chat.h"

gboolean change_insert_to_message(gpointer widget)
{
    GtkAdjustment *adjustment = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW((GtkWidget *)widget));
    gtk_adjustment_set_value(adjustment, gtk_adjustment_get_upper(adjustment));
    return false;
}

gboolean download_message()
{
    if (main_form.current_panel_id == 2)
    {
        char *last_ms_id = get_last_mesage_id("messages.json");
        get_all_messages(data.user_id, last_ms_id);
        message_arr *message_last = get_messages_from_file("messages.json", chats_f.curr_chat);
        create_one_messages(*message_last->length, message_last->messages[*message_last->length - 1], main_form.message_line);
        // g_timeout_add(50, change_insert_to_message, main_form.message_scroll);
        free_messages(message_last);
    }
    return true;
}
