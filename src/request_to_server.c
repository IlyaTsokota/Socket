#include "chat.h"

bool request_to_server(char *request){
    g_print("Start\n");
    int a = write(data.socket_desc, request, strlen(request));
    if (a == (int)strlen(request)) {
        free(request);
        char answer[1024];
        size_t bytes_readed = read(data.socket_desc, answer, 1024);
        answer[bytes_readed] = '\0'; 
        g_print("%s\n", answer);
        return strcmp("1", answer) > 0 ? false : true;
    }
    else {
        free(request);
        g_print("Request to server error!\n");
        return true;
    }
}

