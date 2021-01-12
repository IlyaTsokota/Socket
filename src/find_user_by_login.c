#include "chat.h"

bool find_user_by_login(char *login){
    char *num_f = mx_strnew(strlen("07"));
    num_f ="07";
    char *arr[] = {login, NULL};
    char *json = write_to_json(num_f, arr);
    char *request = g_locale_to_utf8(json, strlen(json), NULL, NULL, NULL);
    free(num_f);
    return request_to_server(request);
}
