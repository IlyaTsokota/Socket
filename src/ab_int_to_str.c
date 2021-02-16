#include "chat.h"

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


char *strjoins_arr(const char **str_arr)
{
    if (str_arr == NULL) return NULL;
    const char **tmp = str_arr;
    char *endstr = NULL;
    ssize_t endlen = 0, i = 0;
    while ((*tmp)) {
        endlen+= strlen(*tmp);
        tmp++;
    }
    endstr = mx_strnew(endlen);
    tmp = str_arr;

    while ((*tmp)) {
         strcpy(&endstr[i], *tmp);
         i+=strlen(*tmp);
         tmp++;
    }
    return endstr;
}