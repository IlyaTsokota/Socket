#include "chat.h"

bool update_user_data(char *u_id, char *name, char *surname, char *quote)
{
    char *num_f = strdup("19");
    char *arr[] = {u_id, name, surname, quote, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    return request_to_server(json);
}
