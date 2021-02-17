#include "server.h"

char *receive_img_to_profile(MYSQL *con, int socket, char *u_id, char *filename) //, char *chat_id, char *message_id)
{

    const char *path_parts[] = {"./user_info/", u_id, NULL};
    char *path_folder = strjoins_arr(path_parts);

    int status = mkdir("./user_info", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    status = mkdir(path_folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    char *file_extension = get_filename_extension(filename);

    char *path_resource = strjoin(3, path_folder, "/icon", file_extension);
    remove(path_resource);
    free(path_folder);
    free(file_extension);

    recieve_image(socket, path_resource);
    //update
    const char *request_parts[] = {"update user set u_avatar = \"", path_resource, "\" where u_id = \"", u_id, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts);
    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }
    free(bdrequest);
    free(path_resource);
    mysql_close(con);

    printf("Image successfully Received!\n");

    return strdup("1");
}

void recieve_image(int socket, char *path)
{
    size_t recv_size = 0;
    uint32_t size ;
    int rc = -1;
    write(socket, &recv_size, sizeof(size_t));
    do {
        rc = read(socket, &size, sizeof(uint32_t));
    } while (rc < 0);
    size = ntohl(size);
    write(socket, &recv_size, sizeof(size_t));
    printf("%u -- total size\n", size);
    printf("Reading Picture Byte Array\n");
    char p_array[1025];
    FILE *image = fopen(path, "w");
    printf("Sending %u\n", size);
    int  nb = 0;
    uint32_t  packet_size = 1024;
    do
    {
        if (packet_size > size)
        {
            packet_size = size;
        }
        printf("PS %u\n", packet_size);
        nb = recv(socket, p_array, packet_size, 0);
        fwrite(p_array, 1, nb, image);
        size -= nb;
        printf("Sending %u\n", size);
    } while (size > 0);
    printf("Sending PGG\n");
    fclose(image);
}

