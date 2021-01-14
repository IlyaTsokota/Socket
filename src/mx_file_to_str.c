#include "chat.h"

char *mx_file_to_str(const char *filename){
    int fileStream = open(filename, O_RDONLY);
    if (fileStream < 0)
    {
        return NULL;
    }
    char c = 0;
    int res = 0;
    int count = 0;
    while ((res = read(fileStream, &c, 1)))
    {
        count++;
    }
    close(fileStream);
    if (count == 0) return NULL;
    char *str = mx_strnew(count);
    if(str == NULL) return NULL;
    int i = 0;
    fileStream = open(filename, O_RDONLY);
    if (fileStream < 0)
    {
        return NULL;
    }
    while ((res = read(fileStream, &c, 1)))
    {
         if (res < 0)
        {
            close(fileStream);
            free(str);
            return NULL;
        }
        str[i++] = c;
    }
    close(fileStream);
    return str;
}
