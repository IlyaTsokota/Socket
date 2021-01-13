#include "chat.h"

bool is_autorization_user(char *login, char *password){
    char *num_f = mx_strnew(strlen("01"));
    strcpy(num_f, "01");
    char *arr[] = { login, password, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    return request_to_server(json);
}
