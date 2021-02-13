#include "chat.h"

char* get_user_id_from_db(char *login){
    char *num_f = strdup("18");
    char *arr[] = {login, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    char *id = request_on_server(data.socket_desc, json);
    free(json);
    return id;
}
