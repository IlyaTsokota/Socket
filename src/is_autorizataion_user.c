#include "chat.h"

bool is_autorization_user(char *login, char *password){
    char *arr[] = {"01", login, password, NULL};
    char **new_arr = array_to_request(arr);
    char *request = array_to_str_with_delimiter(new_arr);
    return request_to_server(request);
}
