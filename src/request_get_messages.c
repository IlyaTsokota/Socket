#include "chat.h"

char *request_on_server(char *request)
{
    int stat;
    long size = 0;
    size_t packet_size = 1024, packet_count = 0, read_index = 0;
    char buff[1024];
    char *str;
    //puts("request = ");
    //puts(request);
    //puts("================");
    write(data.socket_desc, request, strlen(request));

    stat = 1025;

    read(data.socket_desc, (void*)&size, sizeof(long));
    str = mx_strnew(size);

   do {
        if (size < packet_size) {
            packet_size = size;
        }
        stat = recv(data.socket_desc, buff, packet_size, 0);
        memcpy(&str[read_index], buff, packet_size);
        if (stat == -1) {
            perror("[-]Error in sending file.");
            return false;
        }
        size -= stat;
        read_index += stat;
        str[read_index] = '\0';
    } while (size > 0);

    //puts("answer = ");
    //puts(str);
    //puts("================");

    stat = read(data.socket_desc, buff, 1); //ах ты ёбаный ублюдок...
    
    return str;
}