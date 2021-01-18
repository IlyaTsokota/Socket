#include "chat.h"

void get_chats_from_db(GtkWidget *container_chats)
{
    char *num_f = mx_strnew(strlen("17"));
    strcpy(num_f, "17");
    char *arr[] = {"3", NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    chat_t **chats = request_get_chats(json);
    for (size_t i = 0; i < 2; i++)
    {
        puts("------------------------");
        puts(chats[i]->ch_id);
        puts(chats[i]->ch_name);
        puts(chats[i]->ch_avatar);
        puts(chats[i]->u_login);
        puts(chats[i]->u_lastSeen);
        puts(chats[i]->u_avatar);
        puts("------------------------");
    }
}