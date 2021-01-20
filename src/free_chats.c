#include "chat.h"

void free_chats(chat_t **chats){
    if(chats != NULL){
        for(int i = 0; chats[i]; i++){
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