#include "chat.h"

char *cut_str(char *str, int count_sym_cut)
{
    char *status = NULL;
    size_t len = g_utf8_strlen(str, -1);
    if (len > count_sym_cut)
    {
   
        len = count_sym_cut + 3;
        status = mx_strnew(len * 8);
        g_utf8_strncpy(status, str, count_sym_cut);
        g_utf8_strncpy(&status[count_sym_cut - g_utf8_strlen(&str[g_utf8_strlen(str, 1) - 1], 1)], "...\0", 4);
    }
    else
    {
        status = strdup(str);
    }
    return status;
}
