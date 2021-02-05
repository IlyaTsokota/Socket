#include "server.h"

const char *write_validation_login_info_to_json(login_pin_info_t *message)
{
    struct json_object *array;
    struct json_object *object;
    struct json_object *tmp;
    array = json_object_new_array();
    object = json_object_new_object();
    tmp = json_object_new_string(message->u_id);
    json_object_object_add(object, "u_id", tmp);
    tmp = json_object_new_string(message->u_login);
    json_object_object_add(object, "u_login", tmp);
    tmp = json_object_new_string(message->u_avatar);
    json_object_object_add(object, "u_avatar", tmp);

    const char *answer = json_object_to_json_string(object);
    return answer;
}