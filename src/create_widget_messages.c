#include "chat.h"

void create_widget_messages()
{
    message_arr *message = get_messages_from_file("messages.json");
    if (message != NULL)
    {   
        curr_chat.length = malloc(sizeof(int));
        int length = *message->length;

        for (int i = 0; i < length; i++)
        {
           create_one_messages(i, message->messages[i]);
        }
        
        free_messages(message);
    }
}
