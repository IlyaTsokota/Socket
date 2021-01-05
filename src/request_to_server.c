#include "chat.h"

bool request_to_server(char *request){
    int a = write(data.socket_desc, request, strlen(request));
    free(request);
    char answer[1024];
    read(data.socket_desc, answer, 1024);
    return strcmp("1", answer) > 0 ? true : false;
}