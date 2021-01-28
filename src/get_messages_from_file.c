#include "chat.h"

message_t **get_messages_from_file(char *filename, char *chat_id)
{
    puts("Golina\n");
    char *str = mx_file_to_str(filename);
    if (str == NULL) {
        puts("Vse Idet po planu!\n");
    }
    puts("\n");
    puts(str);
    puts("\n");
    int exist = 0;
    json_object *jobj, *values_obj, *tmp_values, *values_name;
    jobj = json_tokener_parse(str);
    if (jobj == NULL) {
        puts("Vse Idet po planu!\n");
    }
    // puts(str);
    free(str);
    exist = json_object_object_get_ex(jobj, "messages", &values_obj);
    int length = json_object_array_length(values_obj);
    if (length > 0)
    {
        int i = 0;
        message_t **messages = malloc(sizeof(message_t *));
        char *tmp;
        for (size_t j = 0; j < length; j++)
        {
            tmp_values = json_object_array_get_idx(values_obj, j);
            json_object_object_get_ex(tmp_values, "ch_id", &values_name);
            tmp = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            if (strcmp(tmp, chat_id) == 0)
            {
                messages[i] = malloc(sizeof(message_t));
                messages[i]->ch_id = strdup(tmp);
                json_object_object_get_ex(tmp_values, "ms_id", &values_name);
                messages[i]->ms_id = strdup((char *)json_object_get_string(values_name));
                free(values_name);
                json_object_object_get_ex(tmp_values, "u_id", &values_name);
                messages[i]->u_id = strdup((char *)json_object_get_string(values_name));
                free(values_name);
                json_object_object_get_ex(tmp_values, "u_name", &values_name);
                messages[i]->u_name = strdup((char *)json_object_get_string(values_name));
                free(values_name);
                json_object_object_get_ex(tmp_values, "u_surname", &values_name);
                messages[i]->u_surname = strdup((char *)json_object_get_string(values_name));
                free(values_name);
                json_object_object_get_ex(tmp_values, "ms_text", &values_name);
                messages[i]->ms_text = strdup((char *)json_object_get_string(values_name));
                free(values_name);
                json_object_object_get_ex(tmp_values, "ms_datetime", &values_name);
                messages[i]->ms_datetime = strdup((char *)json_object_get_string(values_name));
                free(values_name);
                json_object_object_get_ex(tmp_values, "ms_isedited", &values_name);
                messages[i]->ms_isedited = strdup((char *)json_object_get_string(values_name));
                free(values_name);
                json_object_object_get_ex(tmp_values, "ms_isforwarded", &values_name);
                messages[i]->ms_isforwarded = strdup((char *)json_object_get_string(values_name));
                free(values_name);
                json_object_object_get_ex(tmp_values, "ms_ismedia", &values_name);
                messages[i]->ms_ismedia = strdup((char *)json_object_get_string(values_name));
                free(values_name);
                json_object_object_get_ex(tmp_values, "ms_isreply", &values_name);
                messages[i]->ms_isreply = strdup((char *)json_object_get_string(values_name));
                free(values_name);
                json_object_object_get_ex(tmp_values, "ms_isseen", &values_name);
                messages[i]->ms_isseen = strdup((char *)json_object_get_string(values_name));
                free(values_name);
                messages = realloc(messages, (i+2) * sizeof(message_t *));
                i++;
            }
            free(tmp);
            free(tmp_values);
        }
        //messages = realloc(messages, ++i);
        messages[i] = NULL;
        for (size_t v = 0; messages[v]; ++v) {
            puts(messages[v]->ch_id);
            puts("\n/1/1/1/1/1/1/1/1/\n");
        }
        free(values_obj);
        free(jobj);
        return messages;
    }
    free(values_obj);
    free(jobj);
    return NULL;
}