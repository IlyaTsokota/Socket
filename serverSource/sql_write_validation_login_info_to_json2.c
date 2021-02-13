#include "server.h"

const char *write_validation_login_info_to_json2(login_pin_info_t2 *message)
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
    tmp = json_object_new_boolean(message->u_isBottommed);
    json_object_object_add(object, "u_isBottommed", tmp);

    const char *answer = json_object_to_json_string(object);
    return answer;
}