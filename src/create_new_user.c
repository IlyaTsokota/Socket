#include "chat.h"

void create_new_user(char *login, char *name, char *surname, char *password, char *pin){
    char *arr[] = {"03", login , name, surname, password, pin, NULL};
    char **new_arr = array_to_request(arr);
    char *request = array_to_str_with_delimiter(new_arr);   
    request_to_server(request);
}
