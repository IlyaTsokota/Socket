#include "chat.h"

chat_t **request_get_chats(char *request)
{

    write(data.socket_desc, request, strlen(request));
    int buffersize = 0, recv_size = 0, size = 0, read_size , write_size, packet_index = 1, stat;
    char json_array[10241], verify = '1';
    FILE *json_file;

    //Find the size of the image
    do
    {
        stat = read(data.socket_desc, &size, sizeof(int));
    } while (stat < 0);
    g_print("%d -- Size\n", size);
    char buffer[] = "Got it";
    //Send our verification signal
    do
    {
         stat = write(data.socket_desc, &buffer, sizeof(int));
    } while (stat < 0);

    json_file = fopen("chats.json", "w");

    if (json_file == NULL)
    {
        printf("Error has occurred. Image file could not be opened\n");
        return NULL;
    }


    int need_exit = 0;
    struct timeval timeout = {10, 0};

    fd_set fds;
    int buffer_fd, buffer_out;
    while (recv_size < size)
    {
        puts("GG");
        //while(packet_index < 2){

        FD_ZERO(&fds);
        FD_SET(data.socket_desc, &fds);

        buffer_fd = select(FD_SETSIZE, &fds, NULL, NULL, &timeout);

        if (buffer_fd < 0)
            puts("error: bad file descriptor set.\n");

        if (buffer_fd == 0)
            puts("error: buffer read timeout expired.\n");

        if (buffer_fd > 0)
        {
            do
            {
                read_size = read(data.socket_desc, json_array, 10241);
            } while (read_size < 0);

            //Write the currently read data into our image file
            write_size = fwrite(json_array, 1, read_size, json_file);

            if (read_size != write_size)
            {
                puts("error in read write\n");
            }

            recv_size += read_size;
        }
    }

    fclose(json_file);
    char *chats_json = mx_file_to_str("chats.json");
    puts(chats_json);
    free(chats_json);
    // remove("chats.json");

    // struct json_object *jobj;
    // struct json_object *tmp;
    // write(data.socket_desc, request, strlen(request));
    // char answer[1024];
    // size_t bytes_readed = read(data.socket_desc, answer, 1024);
    // answer[bytes_readed] = '\0';
    // write(data.socket_desc, "OK", 2);
    // int size = atoi(answer);
    // if (size > 0)
    // {
    //     chat_t **chats = malloc(sizeof(chat_t *) * (size + 1));
    //     chats[size] = NULL;
    //     for (int i = 0; i < size; i++)
    //     {
    //         bytes_readed = read(data.socket_desc, answer, 1024);
    //         answer[bytes_readed] = '\0';
    //         puts(answer);
    //         chats[i] = malloc(sizeof(chat_t));
    //         jobj = json_tokener_parse(answer);
    //         json_object_object_get_ex(jobj, "ch_id", &tmp);
    //         chats[i]->ch_id = strdup((char *)json_object_get_string(tmp));
    //         free(tmp);
    //         json_object_object_get_ex(jobj, "ch_name", &tmp);
    //         chats[i]->ch_name = strdup((char *)json_object_get_string(tmp));
    //         free(tmp);
    //         json_object_object_get_ex(jobj, "ch_avatar", &tmp);
    //         chats[i]->ch_avatar = strdup((char *)json_object_get_string(tmp));
    //         free(tmp);
    //         json_object_object_get_ex(jobj, "u_login", &tmp);
    //         chats[i]->u_login = strdup((char *)json_object_get_string(tmp));
    //         free(tmp);
    //         json_object_object_get_ex(jobj, "u_last_seen", &tmp);
    //         chats[i]->u_lastSeen = strdup((char *)json_object_get_string(tmp));
    //         free(tmp);
    //         json_object_object_get_ex(jobj, "u_avatar", &tmp);
    //         chats[i]->u_avatar = strdup((char *)json_object_get_string(tmp));
    //         free(tmp);
    //         free(jobj);
    //         write(data.socket_desc, "OK", 2);
    //     }
    //     jobj = tmp = NULL;
    //     return chats;
    // }
    return NULL;
}
