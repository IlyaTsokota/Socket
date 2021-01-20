#include "server.h"

char *strjoins(const char *s1, const char *s2)
{
    char *result = mx_strnew(strlen(s1) + strlen(s2));

    if (result) 
    {
        strcpy(result, s1);
        strcat(result, s2);
    }

    return result;
}
