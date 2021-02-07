#include "server.h"

const char *write_message_back_info_json(message_back_info_t *contact)
{
    struct json_object *array;
    struct json_object *object;
    struct json_object *tmp;
    array = json_object_new_array();
    object = json_object_new_object();
    tmp = json_object_new_string(contact->ms_id);
    json_object_object_add(object, "ms_id", tmp);
    tmp = json_object_new_string(contact->ms_datetime);
    json_object_object_add(object, "ms_datetime", tmp);

    const char *answer = json_object_to_json_string(object);
    return answer;
}
