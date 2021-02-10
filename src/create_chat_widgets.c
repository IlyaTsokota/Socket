#include "chat.h"

void create_chat_widgets(char *user_id)
{
    char *num_f = strdup("17");
    char *arr[] = {user_id, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    char *response = request_on_server(data.socket_desc, json);
    free(json);
    ////puts(response);
    json_object *jobj;
    jobj = json_tokener_parse(response);
    if (jobj == NULL)
    {
        return;
    }
    free(jobj);
    chat_t **chats = request_get_chats(response);
    free(response);
    if (chats != NULL)
    {
        //puts("Ne veselo");
        chats_f.was_free = false;
        int size = 0;
        for (size_t i = 0; chats[i]; i++)
        {
            size++;
        }

        for (size_t i = 0; i < size; i++)
        {
            create_one_chat(i, chats[i]);
        }

        free_chats(chats);
    }
}

void add_one_chat_after_request(char *user_id){
    char *num_f = strdup("17");
    char *arr[] = {user_id, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    char *response = request_on_server(data.socket_desc, json);
    free(json);
    ////puts(response);
    json_object *jobj;
    jobj = json_tokener_parse(response);
    if (jobj == NULL)
    {
        return;
    }
    free(jobj);
    chat_t **chats = request_get_chats(response);
    free(response);
    if (chats != NULL)
    {
        //puts("Ne veselo");
        chats_f.was_free = false;
        int size = 0;
        for (size_t i = 0; chats[i]; i++)
        {
            size++;
        }
        create_one_chat(size, chats[size]);
        free_chats(chats);
    }
}

