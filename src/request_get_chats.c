#include "chat.h"

chat_t **request_get_chats(char *request)
{
    int stat;
    
    size_t packet_size = 1024, packet_count = 0, read_index = 0;
    char buff[1024];
    //buff[1024] = '\0';
    char *str;
    char *tmp = str;
    long size = 0;

    write(data.socket_desc, request, strlen(request));

    stat = 1025;

    read(data.socket_desc, (void*)&size, sizeof(long));

    str = mx_strnew(size);

    do {
        if (size < packet_size) {
            packet_size = size;
        }
        stat = recv(data.socket_desc, buff, packet_size, 0);
        memcpy(&str[read_index], buff, packet_size);
        if (stat == -1) {
            perror("[-]Error in sending file.");
            return false;
        }
        size -= stat;
        read_index += stat;
    } while (size > 0);
    // puts("\n\n\n");
    // puts(str);
    // puts("\n\n\n");
    
    read(data.socket_desc, buff, 1); //ах ты ёбаный ублюдок...

    int exist = 0;
    json_object *jobj, *values_obj, *tmp_values, *values_name;
    jobj = json_tokener_parse(str);
    exist = json_object_object_get_ex(jobj, "chats", &values_obj);
    int length = json_object_array_length(values_obj);
    if (length > 0)
    {
        
        chat_t **chats = malloc(sizeof(chat_t *) * (length + 1));
        chats[length] = NULL;
        for (size_t i = 0; i < length; i++)
        {
            tmp_values = json_object_array_get_idx(values_obj, i);
            chats[i] = malloc(sizeof(chat_t));
            json_object_object_get_ex(tmp_values, "ch_id", &values_name);
            chats[i]->ch_id = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "ch_name", &values_name);
            chats[i]->ch_name = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "ch_avatar", &values_name);
            chats[i]->ch_avatar = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "u_login", &values_name);
            chats[i]->u_login = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "u_last_seen", &values_name);
            chats[i]->u_lastSeen = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "u_avatar", &values_name);
            chats[i]->u_avatar = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            free(tmp_values);
        }
        free(values_obj);
        free(jobj);
        
        return chats;
    }
    free(values_obj);
    free(jobj);
    return NULL;
}
