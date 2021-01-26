#include "chat.h"
#include <strings.h>

char *request_get_messages(char *request)
{
    int size = 0, read_size = 0, stat;
    
    ssize_t packet_size = 1024;
    ssize_t packet_count = 0;
    char buff[1025];
    //buff[1024] = '\0';
    char *str = mx_strnew(0);
    char *tmp = str;

    write(data.socket_desc, request, strlen(request));
    
    stat = 1025;
    read_size = 0;
    read(data.socket_desc, &size, sizeof(int));
   
    while (stat >= packet_size && size > 0) {//= packet_size) {
        stat = recv(data.socket_desc, buff, packet_size, 0);
        buff[stat] = '\0';
       // write(1, int_to_str(stat), strlen(int_to_str(stat)));
        //write(1, "\n", 1);
        //buff[stat] = '\0';
        if (stat <= 0) {
            free(str);
            return NULL;
        }
        //puts(buff);
        //memset(buff, 0, 1024);
        //bzero(&buff, 1024);
        str = strjoins(str, buff);
        size -= packet_size;
    }
    //puts(str);
    return str;
}