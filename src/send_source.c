#include "chat.h"

void send_source(int socket, char *filename)
{
    g_mutex_lock(&main_form.mutex);

    char *num_f = strdup("25");
    puts(filename);
    char *arr[] = {data.user_id, filename, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    write(socket, json, strlen(json));
    free(json);
    FILE *picture;
    ssize_t size;

    picture = fopen(filename, "r");

    if (picture == NULL)
    {
        printf("Error Opening Image File");
    }

    fseek(picture, 0, SEEK_END);
    size = ftell(picture);
    fseek(picture, 0, SEEK_SET);
    printf("Total Picture size: %zu\n", size);
    write(socket, &size, sizeof(size));

    printf("Sending Picture as Byte Array\n");
    char send_buffer[1024];
    while (size > 0)
    {
        fread(send_buffer, 1, 1024, picture);
        write(socket, send_buffer, sizeof(send_buffer));
        size -= 1024;
        // memset(send_buffer, 0, sizeof(send_buffer));
    }
    fclose(picture);
    char buf[1];
    read(socket, buf, 1);
    g_mutex_unlock(&main_form.mutex);
}
