#include "chat.h"

void get_messages_for_current_chat_from_db(GtkWidget *container_msg, char *chat_id)
{
    message_arr *message = get_messages_from_file("messages.json", chat_id);
    if (message != NULL)
    {   
        int length = *message->length;
        for (int i = 0; i < length; i++)
        {
           create_one_messages(i, message->messages[i], container_msg);
        }
        gtk_widget_show_all(container_msg);
        free_messages(message);
    }
}
