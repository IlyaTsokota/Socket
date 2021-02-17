#include "chat.h"

void create_chat_widgets(char *user_id, int sock)
{
    chat_t **chats = take_chats(user_id, sock);
    if (chats != NULL)
    {
        //puts("Ne veselo");

        chats_f.was_free = false;
        int size = 0;
        for (size_t i = 0; chats[i]; i++)
        {
            size++;
        }
        sort_chats(chats, size);
        for (size_t i = 0; i < size; i++)
        {
            create_one_chat(i, chats[i]);
        }

        free_chats(chats);
    }
}

chat_t **take_chats(char *user_id, int sock)
{
    char *num_f = strdup("17");
    char *arr[] = {user_id, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    char *response = request_on_server(sock, json);
    free(json);
    json_object *jobj;
    jobj = json_tokener_parse(response);
    if (jobj == NULL)
    {
        return NULL;
    }
    free(jobj);
    chat_t **chats = request_get_chats(response);
    free(response);
    return chats;
}