#include "chat.h"

bool find_user_by_login(char *login){
    char *arr[] = {"07", login, NULL};
    char **new_arr = array_to_request(arr);
    char *request = array_to_str_with_delimiter(new_arr);
    return request_to_server(request);
}
