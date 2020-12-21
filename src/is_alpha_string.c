#include "chat.h"

bool is_alpha_string(char *str){
    if(str == NULL) 
        return false;
    for (int i = 0; i < strlen(str); i++)
    {
        if(!isalpha(str[i]))
            return false;
    }
    return true;
}