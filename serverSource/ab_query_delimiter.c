#include <server.h>


char *mx_strnew(const int size ){
    char *str = (char *)malloc(sizeof(char) * (size + 1));
    if (str == NULL) 
        return NULL; 
    str[size] = '\0';
    return str;
}

array_t query_delimiter(char* str) 
{
    array_t a;
    char *s = mx_strnew(strlen(str));
    for (unsigned long i = 0; i < strlen(str); i++)
    {
        s[i] = str[i];
    }
    array_init(a);
    array_strtok(&a, s, "~");
    return a;
}

/* разбиение строки на слова */
void array_strtok(array_t *a, char *s, const char *delim)
{
    char *i, *j;
    size_t m, n = 0;

    /* подсчитываем кол-во слов */
    for (i = s; *i; i = j)
    {
        while (*i && (strchr(delim, *i) != NULL))
            ++i;

        j = i;
        while (*j && (strchr(delim, *j) == NULL))
            ++j;

        if (j > i)
            ++n;
    }

    if (!array_resize(a, n))
        return;

    m = 0;
    for (i = strtok(s, delim); i != NULL; i = strtok(NULL, delim))
        a->arr[m++] = strdup(i);
}

/* удаление массива */
void array_clear(array_t *a)
{
    size_t i;
    if (a->arr != NULL)
    {
        for (i = 0; i < a->cnt; ++i)
            free(a->arr[i]);
        free(a->arr);
        a->arr = NULL;
        a->cnt = 0;
    }
}

/* выделение памяти под массив */
int array_resize(array_t *a, size_t n)
{
    size_t i;
    array_clear(a);
    a->arr = (char **)malloc(n * sizeof(char *));
    if (a->arr == NULL)
        return 0;

    for (i = 0; i < n; ++i)
        a->arr[i] = NULL;
    a->cnt = n;
    return 1;
}
