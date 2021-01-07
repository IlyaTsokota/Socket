#include "chat.h"

bool is_login_or_password(int length, int*minSize, char *text){
    return length >= *minSize && is_digit_or_alpha_in_str(text); 
}
