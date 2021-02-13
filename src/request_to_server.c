#include "chat.h"

bool request_to_server(char *request){
    int a = write(data.socket_desc, request, strlen(request));
    if (a == (int)strlen(request)) {
        char answer[1024];
        size_t bytes_readed = read(data.socket_desc, answer, 1024);
        answer[bytes_readed] = '\0';
        puts(answer);
        return strcmp("1", answer) != 0 ? false : true;
    }
    else {
        //g_print("Request to server error!\n");
        return false;
    }
}



char* request_get_str_from_server(char *request){
    int a = write(data.socket_desc, request, strlen(request));
    if (a == (int)strlen(request)) {
        char answer[1024];
        size_t bytes_readed = read(data.socket_desc, answer, 1024);
        answer[bytes_readed] = '\0'; 
        return  strdup(answer);
    }
    else {
        //g_print("Request to server error!\n");
        return NULL;
    }
}


