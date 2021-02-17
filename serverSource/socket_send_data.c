#include "server.h"

bool socket_send_data(char *data, int socket)
{
    if (data == NULL)
        return false;
    ssize_t stat = 0, packet_size = 1024, read_index = 0, size = strlen(data);
    char buff[1024];
    printf("strlen data = --%ld--, data = %s\n", size, data);
    size = htonl(size);
    write(socket, (void *)&size, sizeof(long));
    size = ntohl(size);

    do
    {
        if (size < packet_size)
        {
            packet_size = size;
        }
        memcpy(buff, &data[read_index], packet_size);
        stat = send(socket, buff, packet_size, 0);
        if (stat == -1)
        {
            perror("[-]Error in sending file.");
            return false;
        }
        size -= stat;
        
        read_index += stat;
    } while (size > 0);

    return true;
}
