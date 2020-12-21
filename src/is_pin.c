#include "chat.h"

bool is_pin(int length, int*minSize, char *text){
    return length >= *minSize && is_digits(text); 
}