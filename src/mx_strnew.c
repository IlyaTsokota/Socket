#include "chat.h"

char *mx_strnew(const int size ){
    char *str = (char *)malloc(sizeof(char) * (size + 1));
    if (str == NULL) 
        return NULL; 
    str[size] = '\0';
    return str;
}
