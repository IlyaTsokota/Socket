#include "chat.h"

bool is_digits(char *str) {
    if(str == NULL) 
        return false;
    for (size_t i = 0; i < strlen(str); i++)
    {
        if(!isdigit(str[i]))
            return false;
    }
    return true;
}
