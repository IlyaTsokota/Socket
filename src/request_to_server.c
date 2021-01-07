#include "chat.h"

bool request_to_server(char *request){
    g_print("Start\n");
    int a = write(data.socket_desc, request, strlen(request));
    free(request);
    char answer[1024];
    read(data.socket_desc, answer, 1024);
    g_print("%s\n", answer);
    return strcmp("1", answer) > 0 ? false : true;
}

