#include "chat.h"

void create_new_user(char *login, char *name, char *surname, char *password, char *pin){
    char *num_f = mx_strnew(strlen("03"));
    num_f ="03";
    char *arr[] = { login , name, surname, password, pin, NULL};
    char *json = write_to_json(num_f, arr);
    char *request = g_locale_to_utf8(json, strlen(json), NULL, NULL, NULL);
    free(num_f); 
    request_to_server(request);
}
