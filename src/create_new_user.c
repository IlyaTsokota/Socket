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
    int a = write(data.socket_desc, request, strlen(request));
    free(request);
    char answer[1024];
    read(data.socket_desc, answer, 1024);
    g_print("Сообщение от сервера: %s\n", answer);
}