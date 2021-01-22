#include "chat.h"

message_t **get_messages_from_file(char *filename, char *chat_id){
    char *str = mx_file_to_str(filename);
    int exist = 0;
    json_object *jobj, *values_obj, *tmp_values, *values_name;
    jobj = json_tokener_parse(str);
    free(str);
    exist = json_object_object_get_ex(jobj, "messages", &values_obj);
    int length = json_object_array_length(values_obj);
    if (length > 0)
    {
        message_t **messages = malloc(sizeof(message_t *) * (length + 1));
        messages[length] = NULL;
        for (size_t i = 0; i < length; i++)
        {
            tmp_values = json_object_array_get_idx(values_obj, i);
            messages[i] = malloc(sizeof(chat_t));
            json_object_object_get_ex(tmp_values, "ch_id", &values_name);
            messages[i]->ch_id = strdup((char *)json_object_get_string(values_name));
            free(values_name);
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
            free(tmp_values);
        }
        free(values_obj);
        free(jobj);
        return messages;
    }
    free(values_obj);
    free(jobj);
    return NULL;
}