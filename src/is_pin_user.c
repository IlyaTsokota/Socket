#include "chat.h"

bool is_pin_user(char *pin){
    char *arr[] = {"02", autorization.login_text, pin};
    char **new_arr = (char**)malloc(sizeof(char*) * 3);
    for (int i = 0; i < 3; i++)
    {
        new_arr[i] = (char*)malloc(strlen(arr[i]));
        new_arr[i + 1] = NULL;
        strcpy(new_arr[i], arr[i]);
    }
    char *request = array_to_str_with_delimiter(new_arr, 3);
    return request_to_server(request);
}
