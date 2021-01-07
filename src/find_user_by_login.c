#include "chat.h"

bool find_user_by_login(char *login){
    char **arr = (char**)malloc(sizeof(char*) * 3);
    arr[0] = (char*)malloc(strlen("07"));
    strcpy(arr[0], "07");
    arr[1] = (char*)malloc(strlen(login));
    strcpy(arr[1], login);
    arr[2] = NULL;
    char *request = array_to_str_with_delimiter(arr, 2);
    return request_to_server(request);
}
