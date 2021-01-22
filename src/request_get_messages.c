#include "chat.h"

char *request_get_messages(char *request)
{
    int size = 0, read_size = 0, stat;
    
    ssize_t packet_size = 1024;
    ssize_t packet_count = 0;
    char buff[1025];
    buff[1024] = '\0';
    char *str = mx_strnew(0);
    char *tmp = str;

    write(data.socket_desc, request, strlen(request));
    
    stat = 1025;
    read_size = 0;
   
    while (stat >= packet_size) {
        stat = recv(data.socket_desc, buff, packet_size, 0);
        buff[stat-1] = '\0';
        if (stat <= 0) {
            free(str);
            return NULL;
        }
        str = strjoins(str, buff);
    }
    return str;
}
