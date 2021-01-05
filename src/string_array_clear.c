#include "chat.h"

void string_array_clear(char **arr, int size)
{
    if (arr != NULL)
    {
        for (int i = 0; i < size; ++i)
            free(arr[i]);
        free(arr);
        arr = NULL;
    }
}
