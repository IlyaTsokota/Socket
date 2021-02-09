#include "server.h"

char *receive_image(int socket, char *chat_id, char *message_id)
{ // Start function

    int buffersize = 0, recv_size = 0, size = 0, read_size, write_size, packet_index = 1, stat;
    char imagearray[10241], verify = '1';
    FILE *image;
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

    printf("Reply sent\n");
    printf(" \n");
    const char *path_parts[] = {"./", chat_id, "/", message_id, ".png", NULL};
    char *path = strjoins_arr(path_parts);
    puts(path);
    image = fopen("path", "w");

    if (image == NULL)
    {
        printf("Error has occurred. Image file could not be opened\n");
        return "0";
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
    return "1";
}