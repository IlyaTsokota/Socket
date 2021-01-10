#include "chat.h"

bool is_pin_user(char *pin){
    char *arr[] = {"02", autorization.login_text, pin, NULL};
    char **new_arr = array_to_request(arr);
    char *request = array_to_str_with_delimiter(new_arr);
    return request_to_server(request);
}
