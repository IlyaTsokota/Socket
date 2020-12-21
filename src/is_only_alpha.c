#include "chat.h"

bool is_only_alpha(int length, int*minSize, char *text){
    return length >= *minSize && is_alpha_string(text); 
}