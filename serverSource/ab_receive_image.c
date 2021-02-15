#include "server.h"

char *receive_img_to_profile(MYSQL con, int socket, char *u_id, char *filename) //, char *chat_id, char *message_id)
{

    int buffersize = 0, recv_size = 0, size = 0, read_size, write_size, packet_index = 1, stat;
    char imagearray[10241], verify = '1';

    //Find the size of the image
    do
    {
        stat = read(socket, &size, sizeof(int));
    } while (stat < 0);

    printf("Packet received.\n");
    printf("Packet size: %i\n", stat);
    printf("Image size: %i\n", size);
    printf(" \n");

    char buffer[] = "Got it";

    //Send our verification signal
    do
    {
        stat = write(socket, &buffer, sizeof(int));
    } while (stat < 0);

    const char *path_parts[] = {"./user_info/", u_id, NULL};
    char *path_folder = strjoins_arr(path_parts);

    int status = mkdir("./user_info", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    status = mkdir(path_folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    char *file_extension = get_filename_extension(filename);

    char *path_resource = strjoin(3, path_folder, "/icon", file_extension);
    remove(path_resource);
    FILE *image = fopen(path_resource, "w");
    free(path_folder);
    free(file_extension);

    //update
    const char *request_parts[] = {"update user set u_avatar = \"", path_folder, "\" where u_id = \"", u_id, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts);
    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }
    mysql_close(con);
    free(bdrequest);
    free(path_resource);

    if (image == NULL)
    {
        printf("Error has occurred. Image file could not be opened\n");
        return strdup("0");
    }

    //Loop while we have not received the entire file yet

    int need_exit = 0;
    struct timeval timeout = {10, 0};

    fd_set fds;
    int buffer_fd, buffer_out;

    while (recv_size < size)
    {
        //while(packet_index < 2){

        FD_ZERO(&fds);
        FD_SET(socket, &fds);

        buffer_fd = select(FD_SETSIZE, &fds, NULL, NULL, &timeout);

        if (buffer_fd < 0)
            printf("error: bad file descriptor set.\n");

        if (buffer_fd == 0)
            printf("error: buffer read timeout expired.\n");

        if (buffer_fd > 0)
        {
            do
            {
                read_size = read(socket, imagearray, 10241);
            } while (read_size < 0);

            printf("Packet number received: %i\n", packet_index);
            printf("Packet size: %i\n", read_size);

            //Write the currently read data into our image file
            write_size = fwrite(imagearray, 1, read_size, image);
            printf("Written image size: %i\n", write_size);

            if (read_size != write_size)
            {
                printf("error in read write\n");
            }

            //Increment the total number of bytes read
            recv_size += read_size;
            packet_index++;
            printf("Total received image size: %i\n", recv_size);
            printf(" \n");
            printf(" \n");
        }
    }

    fclose(image);

    printf("Image successfully Received!\n");
    return strdup("1");
}