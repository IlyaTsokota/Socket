#include "chat.h"

char *request_on_server(int socket, char *request)
{
    g_mutex_lock(&main_form.mutex);
    int stat;
    long size = 0;
    size_t packet_size = 1024, packet_count = 0, read_index = 0;
    char buff[1024];
    char *str;
    puts("request = ");
    puts(request);
    puts("================");

    write(socket, request, strlen(request));

    stat = 1025;
    
    read(socket, (void *)&size, sizeof(long));
    size = ntohl(size);

    str = mx_strnew(size);

    do
    {
        if (size < packet_size)
        {
            packet_size = size;
        }
        stat = recv(socket, buff, packet_size, 0);
        memcpy(&str[read_index], buff, packet_size);
        if (stat == -1)
        {
            perror("[-]Error in sending file.");
            return NULL;
        }
        size -= stat;
        read_index += stat;
        str[read_index] = '\0';

    } while (size > 0);

    // puts("answer = ");
    // puts(str);
    // puts("================");

    stat = read(socket, buff, 1); //ах ты ёбаный ублюдок...
    g_mutex_unlock(&main_form.mutex);
    return str;
}


