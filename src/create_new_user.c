#include "chat.h"

void create_new_user(char *login, char *name, char *surname, char *password, char *pin){
    char *arr[] = {"03", login , name, surname, password, pin};
    char **new_arr = (char**)malloc(sizeof(char*));
    for (int i = 0; i < 6; i++)
    {
        new_arr[i] = (char*)malloc(strlen(arr[i]));
        new_arr[i + 1] = NULL;
        strcpy(new_arr[i], arr[i]);
    }
    char *request = array_to_str_with_delimiter(new_arr, 6);
    bool b = request_to_server(request);
}