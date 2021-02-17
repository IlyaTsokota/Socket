#include "chat.h"

bool request_to_server(char *request){
    g_mutex_lock(&main_form.mutex);
    int a = write(data.socket_desc, request, strlen(request));
    if (a == (int)strlen(request)) {
        char answer[1024];
        size_t bytes_readed = read(data.socket_desc, answer, 1024);
        answer[bytes_readed] = '\0';
        g_mutex_unlock(&main_form.mutex);
        return strcmp("1", answer) != 0 ? false : true;
    }
    else {
        g_mutex_unlock(&main_form.mutex);

        // //g_print("Request to server error!\n");
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
        // //g_print("Request to server error!\n");
        return NULL;
    }
}


