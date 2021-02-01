#include "chat.h"

void free_chats(chat_t **chats)
{
    if (chats != NULL)
    {
        for (int i = 0; chats[i]; i++)
        {
            free(chats[i]->ch_id);
            free(chats[i]->ch_name);
            free(chats[i]->ch_avatar);
            free(chats[i]->u_avatar);
            free(chats[i]->u_lastSeen);
            free(chats[i]->u_login);
            free(chats[i]);
        }
        free(chats);
        chats = NULL;
    }
}

void free_messages(message_arr *message_container)
{
    if (message_container != NULL)
    {
        for (int i = 0; i < *message_container->length; i++)
        {

            free(message_container->messages[i]->ms_datetime);
            free(message_container->messages[i]->ms_id);
            free(message_container->messages[i]->ms_isedited);
            free(message_container->messages[i]->ms_isforwarded);
            free(message_container->messages[i]->ms_ismedia);
            free(message_container->messages[i]->ms_isreply);
            free(message_container->messages[i]->ms_isseen);
            free(message_container->messages[i]->ms_text);
            free(message_container->messages[i]->u_id);
            free(message_container->messages[i]->u_name);
            free(message_container->messages[i]);
        }
        free(message_container->messages);
        free(message_container->length);
        free(message_container);
        message_container->messages = NULL;
        message_container = NULL;
    }
}
