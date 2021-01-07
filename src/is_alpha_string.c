#include "chat.h"

bool is_alpha_string(char *str){
    if(str == NULL) 
        return false;
    for (int i = 0; i < (int)strlen(str); i++)
    {
        if(!isalpha(str[i]) || !iswalpha(str[i]))
            return false;
    }
    return true;
}
