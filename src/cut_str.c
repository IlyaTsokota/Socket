#include "chat.h"

char *cut_str(char *str, int count_sym_cut)
{
    char *status = NULL;
    size_t len = g_utf8_strlen(str, -1);
    if (len > count_sym_cut)
    {
        int i = 0;
        len = count_sym_cut + 3;
        status = mx_strnew(len * 8);
        status = memset(status, '\0', len * 8);
        g_utf8_strncpy(status, str, count_sym_cut);
        while (status[i] != '\0') {
            ++i;
        }
        g_utf8_strncpy(&status[i], "...\0", 4);
        return status;
    }
    else
    {
        status = strdup(str);
    }
    return status;
}
