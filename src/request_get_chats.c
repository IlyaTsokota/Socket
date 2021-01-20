#include "chat.h"

chat_t **request_get_chats(char *request)
{

    write(data.socket_desc, request, strlen(request));
    int buffersize = 0, recv_size = 0, size = 0, read_size , write_size, packet_index = 1, stat;
    char json_array[1024], verify = '1';
    //Find the size of the image
    do
    {
        stat = read(data.socket_desc, &size, sizeof(int));
    } while (stat < 0);
    g_print("%d -- Size\n", size);
    
    ssize_t packet_size = 1024;
    ssize_t packet_count = 0;
    ssize_t bytes_recieved = 0;
    char *str = mx_strnew(size);
    do
    {
        read_size = read(data.socket_desc, &str[bytes_recieved], 1024);
        bytes_recieved += read_size;
    } while (read_size < 0 && bytes_recieved != strlen(json_array));

    puts(str);

    struct json_object *jobj;
    struct json_object *tmp;
    write(data.socket_desc, request, strlen(request));
    char answer[1024];
    size_t bytes_readed = read(data.socket_desc, answer, 1024);
    answer[bytes_readed] = '\0';
    write(data.socket_desc, "OK", 2);
    int size = atoi(answer);
    if (size > 0)
    {
        chat_t **chats = malloc(sizeof(chat_t *) * (size + 1));
        chats[size] = NULL;
        for (int i = 0; i < size; i++)
        {
            bytes_readed = read(data.socket_desc, answer, 1024);
            answer[bytes_readed] = '\0';
            puts(answer);
            chats[i] = malloc(sizeof(chat_t));
            jobj = json_tokener_parse(answer);
            json_object_object_get_ex(jobj, "ch_id", &tmp);
            chats[i]->ch_id = strdup((char *)json_object_get_string(tmp));
            free(tmp);
            json_object_object_get_ex(jobj, "ch_name", &tmp);
            chats[i]->ch_name = strdup((char *)json_object_get_string(tmp));
            free(tmp);
            json_object_object_get_ex(jobj, "ch_avatar", &tmp);
            chats[i]->ch_avatar = strdup((char *)json_object_get_string(tmp));
            free(tmp);
            json_object_object_get_ex(jobj, "u_login", &tmp);
            chats[i]->u_login = strdup((char *)json_object_get_string(tmp));
            free(tmp);
            json_object_object_get_ex(jobj, "u_last_seen", &tmp);
            chats[i]->u_lastSeen = strdup((char *)json_object_get_string(tmp));
            free(tmp);
            json_object_object_get_ex(jobj, "u_avatar", &tmp);
            chats[i]->u_avatar = strdup((char *)json_object_get_string(tmp));
            free(tmp);
            free(jobj);
            write(data.socket_desc, "OK", 2);
        }
        jobj = tmp = NULL;
        return chats;
    }
    return NULL;
}
