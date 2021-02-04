#include "chat.h"
char *strjoin(int nHowMany, ... ) {
    if (nHowMany <= 0) return NULL; 
    char **args = (char**)malloc(sizeof(char*) * nHowMany);
    char* endStr = NULL;
    ssize_t endStrLen = 0, j = 0;
    //
    va_list charPtrArgumentPointer;
    va_start(charPtrArgumentPointer, nHowMany);
    for(int i = 0; i < nHowMany; i++) {
        args[i] = va_arg(charPtrArgumentPointer, char*);
        endStrLen += strlen(args[i]);
    }
    va_end(charPtrArgumentPointer);
    endStr = mx_strnew(endStrLen);
    for(int i = 0; i < nHowMany; i++) {
        strcpy(&endStr[j], args[i]);
        j += strlen(args[i]);
    }
    free(args);
    args = NULL;
    //
    return endStr;
}
