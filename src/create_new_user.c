#include "chat.h"

void create_new_user(char *login, char *name, char *surname, char *password, char *pin){
    char *num_f = mx_strnew(strlen("03"));
    strcpy(num_f, "03");
    char *arr[] = { login , name, surname, password, pin, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    request_to_server(json);
    
}
