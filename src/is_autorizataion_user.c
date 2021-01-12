#include "chat.h"

bool is_autorization_user(char *login, char *password){
    char *num_f = mx_strnew(strlen("01"));
    num_f ="01";
    char *arr[] = { login, password, NULL};
    char *json = write_to_json(num_f, arr);
    char *request = g_locale_to_utf8(json, strlen(json), NULL, NULL, NULL);
    free(num_f);
    return request_to_server(request);
}
