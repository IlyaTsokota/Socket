#include "server.h"

static void reverse_string(char *str)
{
    /* skip null */
    if (str == NULL)
    {
        return;
    }

    /* skip empty string */
    if (*str == 0)
    {
        return;
    }

    /* get range */
    char *start = str;
    char *end = start + strlen(str) - 1; /* -1 for \0 */
    char temp;

    /* reverse */
    while (end > start)
    {
        /* swap */
        temp = *start;
        *start = *end;
        *end = temp;

        /* move */
        ++start;
        --end;
    }
}


char* int_to_str(int n) 
{
    if (n != 0) {
        int j=0, i=0, strlen = 0;
        long val = n;
        while (val != 0) {
            strlen++;
            val /= 10;
        }
        
        val = n;
        if (val < 0) {
            val = -val;
            strlen++;
        }
        char *str = mx_strnew(strlen);
        while (val != 0) {
            str[i++] = val % 10 + '0';
            val /= 10;
        }
        if (n < 0)
            str[i++] = '-';
        reverse_string(str);
       return str;
    } else {
       return NULL;
    }
}