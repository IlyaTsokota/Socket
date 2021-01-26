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

void free_messages(message_t **messages){
     if(messages != NULL){
        for(int i = 0; messages[i]; i++){
            free(messages[i]->ch_id);
            free(messages[i]->ms_datetime);
            free(messages[i]->ms_id);
            free(messages[i]->ms_isedited);
            free(messages[i]->ms_isforwarded);
            free(messages[i]->ms_ismedia);
            free(messages[i]->ms_isreply);
            free(messages[i]->ms_isseen);
            free(messages[i]->ms_text);
            free(messages[i]->u_id);
            free(messages[i]->u_name);
            free(messages[i]->u_surname);
            free(messages[i]);
        }
         free(messages);
         messages = NULL;
    }
}
