#include "chat.h"

chat_t **request_get_chats(char *request)
{

    write(data.socket_desc, request, strlen(request));
    int size = 0, read_size = 0, stat;
    //Find the size of the image
    //    do
    //    {
    //        stat = read(data.socket_desc, &size, sizeof(int));
    //    } while (stat < 0);
    //    g_print("%d -- Size\n", size);

    ssize_t packet_size = 1024;
    ssize_t packet_count = 0;
    char *str = mx_strnew(4 * packet_size);
    if (str == NULL)
    {
        g_print("UY\n");
    }
    stat = 0;
    char *tmp = str;
    do
    {
        read_size = read(data.socket_desc, &str[stat], packet_size);
        str[stat - 1] = '\0';
        // g_print("%s -- read_str\n", &str[stat]);
        stat += read_size;
        ++packet_count;
        if (packet_count > 3)
        {
            str = realloc(str, sizeof(char) * (packet_count * packet_size * 4 + 1));
        }

    } while (read_size >= packet_size);

    // g_print("%lu -- strlen-Size\n", strlen(str));
    //str[size+1] = '\0';
    // puts(str);
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