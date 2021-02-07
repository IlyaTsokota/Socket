#include "chat.h"

message_arr *take_messages(char *user_id, char *last_msg_id)
{
    char *num_f = strdup("16");
    char *arr[] = {user_id, last_msg_id, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    char *messages = request_on_server(json);
    puts(messages);
    free(json);
    message_arr *messages_s = messages_to_json(messages);
    
    free(messages);
    if(messages_s == NULL)
        return NULL;
    return messages_s;
}

message_arr *messages_to_json(char *str)
{
    json_object *jobj, *values_obj, *tmp_values, *values_name;
    jobj = json_tokener_parse(str);
     int exist = 0;
    if(jobj == NULL) return NULL;
    exist = json_object_object_get_ex(jobj, "messages", &values_obj);
    int length = json_object_array_length(values_obj);
    if (length > 0)
    {
        int i = 0;
        message_arr *arr_msgs = malloc(sizeof(message_arr));
        arr_msgs->messages = malloc(sizeof(message_t *));
        char *tmp;
        for (size_t j = 0; j < length; j++)
        {
            tmp_values = json_object_array_get_idx(values_obj, j);
            
            arr_msgs->messages[i] = malloc(sizeof(message_t));
            json_object_object_get_ex(tmp_values, "ch_id", &values_name);
            arr_msgs->messages[i]->ch_id = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "ms_id", &values_name);
            arr_msgs->messages[i]->ms_id = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "u_id", &values_name);
            arr_msgs->messages[i]->u_id = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "u_name", &values_name);
            arr_msgs->messages[i]->u_name = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "ms_text", &values_name);
            arr_msgs->messages[i]->ms_text = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "ms_datetime", &values_name);
            arr_msgs->messages[i]->ms_datetime = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "ms_isedited", &values_name);
            arr_msgs->messages[i]->ms_isedited = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "ms_isforwarded", &values_name);
            arr_msgs->messages[i]->ms_isforwarded = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "ms_ismedia", &values_name);
            arr_msgs->messages[i]->ms_ismedia = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "ms_isreply", &values_name);
            arr_msgs->messages[i]->ms_isreply = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "ms_isseen", &values_name);
            arr_msgs->messages[i]->ms_isseen = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            arr_msgs->messages = realloc(arr_msgs->messages, (i + 2) * sizeof(message_t *));
            free(tmp_values);
            i++;
        }
        arr_msgs->messages[i] = NULL;
        free(values_obj);
        free(jobj);
        arr_msgs->length = malloc(sizeof(int));
        *(arr_msgs->length) = i ;
        return arr_msgs;
    }
    free(values_obj);
    free(jobj);
    return NULL;
}
