#include "chat.h"

void send_source(int so, char *filename)
{
    g_mutex_lock(&main_form.mutex);
    struct sockaddr_in client_addr;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    int port = 3762;
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = INADDR_ANY; // inet_addr("159.224.0.212"); //inet_addr("178.165.30.151");
    client_addr.sin_port = htons(port);

    if (connect(sock, (struct sockaddr *)&client_addr, sizeof(client_addr)) == 0)
    {
        char *num_f = strdup("25");
        puts(filename);
        char *arr[] = {data.user_id, filename, NULL};
        char *json = write_to_json(num_f, arr);
        free(num_f);
        write(sock, json, strlen(json));
        free(json);
        send_image(sock, filename);
    }

    close(sock);
    g_mutex_unlock(&main_form.mutex);
}

void send_image(int sock, char *filename)
{
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
    char b[1];
    read(sock, &b, 1);
}

void recieve_image(int socket, char *path)
{
    size_t recv_size = 0;
    long long size;
    write(socket, &recv_size, sizeof(size_t));
    recv(socket, &size, sizeof(long long), 0);
    write(socket, &recv_size, sizeof(size_t));

    printf("Reading Picture Byte Array\n");
    char p_array[1025];
    FILE *image = fopen(path, "w");
    printf("Sending %lld\n", size);
    long long nb = 0;
    long long packet_size = 1024;
    do
    {
        if (packet_size > size)
        {
            packet_size = size;
        }
        printf("PS %lld\n", packet_size);
        nb = recv(socket, p_array, packet_size, 0);
        fwrite(p_array, 1, nb, image);
        size -= nb;
        printf("Sending %lld\n", size);
    } while (size > 0);
    printf("Sending PGG\n");
    fclose(image);
    char b[1];
    read(socket, &b, 1);
}



char *get_filename_extension(char *filename){
 
    int index = 0;
    for (int i = strlen(filename) - 1; i >= 0; i--)
    {
        if(filename[i] == '.'){
            index = i;
            break;
        }
    }
   char *result = strdup(&filename[index]);
   return result;
}
