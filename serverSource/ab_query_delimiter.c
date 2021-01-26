#include <server.h>


char *mx_strnew(const int size ){
    char *str = (char *)malloc(sizeof(char) * (size + 1));
    if (str == NULL) 
        return NULL; 
    str[size] = '\0';
    return str;
}

/* удаление массива */
void array_clear(array_t *a)
{
    if (a->arr != NULL)
    {
        for (size_t i = 0; i < a->cnt; ++i)
            free(a->arr[i]);
        free(a->arr);
        a->arr = NULL;
        a->cnt = 0;
    }
}
