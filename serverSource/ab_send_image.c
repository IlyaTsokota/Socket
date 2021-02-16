#include "server.h"

char *send_image(int sock, char *filename)
{
    puts(filename);
    size_t lol;
    FILE *picture = fopen(filename, "r");
    fseek(picture, 0, SEEK_END);
    long long size = ftell(picture);
    fseek(picture, 0, SEEK_SET);
    read(sock, &lol, sizeof(size_t));
    send(sock, &size, sizeof(long long), 0);
    read(sock, &lol, sizeof(size_t));
    printf("Sending Picture as Byte Array\n");
    char send_buffer[1025]; // no link between BUFSIZE and the file size
    int nb = 0, nb1 = 0;
    do
    {
        nb1 = fread(send_buffer, 1, 1024, picture);
        nb = send(sock, send_buffer, nb1, 0);
        size -= nb;
    } while (size > 0);
    printf("Sending PGG\n");
    fclose(picture);
    return strdup("1");
}