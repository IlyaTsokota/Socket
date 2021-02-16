#include <server.h>

char *mx_strnew(const int size)
{
    char *str = (char *)malloc(sizeof(char) * (size + 1));
    if (str == NULL)
        return NULL;
    str[size] = '\0';
    return str;
}

/* удаление массива */
void array_clear(array_t *a)
{
    if (a != NULL && a->arr != NULL)
    {
        for (int i = 0; a->arr[i]; i++)
        {
            if(a->arr[i] != NULL)
                free(a->arr[i]);
        }
        free(a->arr);
        a->arr = NULL;
        a->cnt = 0;
    }
}
