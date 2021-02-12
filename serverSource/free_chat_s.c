#include "server.h"

void free_chat_s(chat_t *chat){
 if (chat != NULL)
    {
        free(chat->ch_id);
        free(chat->ch_name);
        free(chat->ch_avatar);
        free(chat->u_avatar);
        free(chat->u_login);
        free(chat->u_lastSeen);
        free(chat);
        chat = NULL;
    }
}
