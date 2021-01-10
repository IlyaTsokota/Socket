#include "chat.h"
//char *user_add(MYSQL *con, char *login, char *name, char *surname, char *password, char *pin)
char *array_to_str_with_delimiter(char **arr)
{
    int length =0;
    char **arr_temp = arr;
    while(*arr){
        ++length;
        ++arr;
    }
    arr = arr_temp;
    int new_str_length = 0;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < (int)strlen(arr[i]); j++)
        {
            new_str_length++;
        }
        new_str_length++;
    }
    char *str = mx_strnew(new_str_length);
    int k = 0;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < (int)strlen(arr[i]); j++)
        {
            str[k++] = arr[i][j];
        }
        str[k++] = '~';
    }
    string_array_clear(arr, length);
    return str;
}
