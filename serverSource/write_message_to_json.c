#include "server.h"

const char *write_message_to_json(message_t *message)
{
    struct json_object *array;
    struct json_object *object;
    struct json_object *tmp;
    array = json_object_new_array();
    object = json_object_new_object();
    tmp = json_object_new_string(message->ch_id);
    json_object_object_add(object, "ch_id", tmp);
    tmp = json_object_new_string(message->ms_id);
    json_object_object_add(object, "ms_id", tmp);
    tmp = json_object_new_string(message->u_id);
    json_object_object_add(object, "u_id", tmp);
    tmp = json_object_new_string(message->u_name);
    json_object_object_add(object, "u_name", tmp);
    tmp = json_object_new_string(message->ms_text);
    json_object_object_add(object, "ms_text", tmp);
    tmp = json_object_new_string(message->ms_datetime);
    json_object_object_add(object, "ms_datetime", tmp);
    tmp = json_object_new_string(message->ms_isedited);
    json_object_object_add(object, "ms_isedited", tmp);
    tmp = json_object_new_string(message->ms_isforwarded);
    json_object_object_add(object, "ms_isforwarded", tmp);
    tmp = json_object_new_string(message->ms_ismedia);
    json_object_object_add(object, "ms_ismedia", tmp);
    tmp = json_object_new_string(message->ms_isreply);
    json_object_object_add(object, "ms_isreply", tmp);
    tmp = json_object_new_string(message->ms_isseen);
    json_object_object_add(object, "ms_isseen", tmp);

    const char *answer = json_object_to_json_string(object);
    return answer;
}
