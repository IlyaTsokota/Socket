#include "chat.h"

bool is_digit_or_alpha_in_str(char *str){
    if(str == NULL) 
        return false;
    for (int i = 0; i < (int)strlen(str); i++)
    {
        if(!isdigit(str[i]) && !isalpha(str[i]))
            return false;
    }
    return true;
}
