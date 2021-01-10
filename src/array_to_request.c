#include "chat.h"

char **array_to_request(char **arr){
    int size =0;
    char **arr_temp = arr;
    while(*arr){
        ++size;
        ++arr;
    }
    arr = arr_temp;
    char **new_arr = (char**)malloc(sizeof(char*) * (size + 1));
    for (int i = 0; i < size; i++)
    {
        new_arr[i] = g_locale_to_utf8(arr[i], strlen(arr[i]), NULL, NULL, NULL);
        new_arr[i + 1] = NULL;
    }
    return new_arr;
}
